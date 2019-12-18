#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u_long ;
typedef  int u32 ;
struct sym_hcb {int rv_ctest4; int hcb_ba; int /*<<< orphan*/  scratch; } ;

/* Variables and functions */
 int BF ; 
 int DIP ; 
 int IID ; 
 int INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int INL (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int INTF ; 
 int MDPE ; 
 int MPEE ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL (struct sym_hcb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,int) ; 
 int SCRIPTZ_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int SIP ; 
 int SYM_SNOOP_TIMEOUT ; 
 int /*<<< orphan*/  cpu_to_scr (int) ; 
 int /*<<< orphan*/  nc_ctest4 ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_dstat ; 
 int /*<<< orphan*/  nc_istat ; 
 int /*<<< orphan*/  nc_scratcha ; 
 int /*<<< orphan*/  nc_temp ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int scr_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snoopend ; 
 int /*<<< orphan*/  snooptest ; 
 char* sym_name (struct sym_hcb*) ; 
 int sym_regtest (struct sym_hcb*) ; 

__attribute__((used)) static int sym_snooptest(struct sym_hcb *np)
{
	u32 sym_rd, sym_wr, sym_bk, host_rd, host_wr, pc, dstat;
	int i, err;

	err = sym_regtest(np);
	if (err)
		return err;
restart_test:
	/*
	 *  Enable Master Parity Checking as we intend 
	 *  to enable it for normal operations.
	 */
	OUTB(np, nc_ctest4, (np->rv_ctest4 & MPEE));
	/*
	 *  init
	 */
	pc  = SCRIPTZ_BA(np, snooptest);
	host_wr = 1;
	sym_wr  = 2;
	/*
	 *  Set memory and register.
	 */
	np->scratch = cpu_to_scr(host_wr);
	OUTL(np, nc_temp, sym_wr);
	/*
	 *  Start script (exchange values)
	 */
	OUTL(np, nc_dsa, np->hcb_ba);
	OUTL_DSP(np, pc);
	/*
	 *  Wait 'til done (with timeout)
	 */
	for (i=0; i<SYM_SNOOP_TIMEOUT; i++)
		if (INB(np, nc_istat) & (INTF|SIP|DIP))
			break;
	if (i>=SYM_SNOOP_TIMEOUT) {
		printf ("CACHE TEST FAILED: timeout.\n");
		return (0x20);
	}
	/*
	 *  Check for fatal DMA errors.
	 */
	dstat = INB(np, nc_dstat);
#if 1	/* Band aiding for broken hardwares that fail PCI parity */
	if ((dstat & MDPE) && (np->rv_ctest4 & MPEE)) {
		printf ("%s: PCI DATA PARITY ERROR DETECTED - "
			"DISABLING MASTER DATA PARITY CHECKING.\n",
			sym_name(np));
		np->rv_ctest4 &= ~MPEE;
		goto restart_test;
	}
#endif
	if (dstat & (MDPE|BF|IID)) {
		printf ("CACHE TEST FAILED: DMA error (dstat=0x%02x).", dstat);
		return (0x80);
	}
	/*
	 *  Save termination position.
	 */
	pc = INL(np, nc_dsp);
	/*
	 *  Read memory and register.
	 */
	host_rd = scr_to_cpu(np->scratch);
	sym_rd  = INL(np, nc_scratcha);
	sym_bk  = INL(np, nc_temp);
	/*
	 *  Check termination position.
	 */
	if (pc != SCRIPTZ_BA(np, snoopend)+8) {
		printf ("CACHE TEST FAILED: script execution failed.\n");
		printf ("start=%08lx, pc=%08lx, end=%08lx\n", 
			(u_long) SCRIPTZ_BA(np, snooptest), (u_long) pc,
			(u_long) SCRIPTZ_BA(np, snoopend) +8);
		return (0x40);
	}
	/*
	 *  Show results.
	 */
	if (host_wr != sym_rd) {
		printf ("CACHE TEST FAILED: host wrote %d, chip read %d.\n",
			(int) host_wr, (int) sym_rd);
		err |= 1;
	}
	if (host_rd != sym_wr) {
		printf ("CACHE TEST FAILED: chip wrote %d, host read %d.\n",
			(int) sym_wr, (int) host_rd);
		err |= 2;
	}
	if (sym_bk != sym_wr) {
		printf ("CACHE TEST FAILED: chip wrote %d, read back %d.\n",
			(int) sym_wr, (int) sym_bk);
		err |= 4;
	}

	return err;
}