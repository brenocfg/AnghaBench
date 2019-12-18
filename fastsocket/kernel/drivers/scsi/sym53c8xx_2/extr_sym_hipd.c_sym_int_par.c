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
typedef  int u_short ;
typedef  int u_char ;
typedef  int u32 ;
struct sym_hcb {int /*<<< orphan*/ * msgout; } ;
struct sym_ccb {int /*<<< orphan*/  xerr_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  HF_EXT_ERR ; 
 int /*<<< orphan*/  HF_PRT ; 
 int /*<<< orphan*/  HS_PRT ; 
 int /*<<< orphan*/  HS_UNEXPECTED ; 
 int INB (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int INL (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int ISCON ; 
 int MA ; 
 int /*<<< orphan*/  M_ID_ERROR ; 
 int /*<<< orphan*/  M_PARITY ; 
 int /*<<< orphan*/  OUTL_DSP (struct sym_hcb*,int) ; 
 int /*<<< orphan*/  OUTONB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SCRIPTA_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int SCRIPTB_BA (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XE_PARITY_ERR ; 
 int /*<<< orphan*/  clrack ; 
 int /*<<< orphan*/  dispatch ; 
 int /*<<< orphan*/  nc_dbc ; 
 int /*<<< orphan*/  nc_dsa ; 
 int /*<<< orphan*/  nc_dsp ; 
 int /*<<< orphan*/  nc_sbcl ; 
 int /*<<< orphan*/  nc_scntl1 ; 
 int /*<<< orphan*/  pm_handle ; 
 int /*<<< orphan*/  printf (char*,char*,int,int,int) ; 
 scalar_t__ printk_ratelimit () ; 
 struct sym_ccb* sym_ccb_from_dsa (struct sym_hcb*,int) ; 
 int /*<<< orphan*/  sym_int_ma (struct sym_hcb*) ; 
 char* sym_name (struct sym_hcb*) ; 
 int /*<<< orphan*/  sym_recover_scsi_int (struct sym_hcb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_set_script_dp (struct sym_hcb*,struct sym_ccb*,int) ; 
 int /*<<< orphan*/  sym_start_reset (struct sym_hcb*) ; 

__attribute__((used)) static void sym_int_par (struct sym_hcb *np, u_short sist)
{
	u_char	hsts	= INB(np, HS_PRT);
	u32	dsp	= INL(np, nc_dsp);
	u32	dbc	= INL(np, nc_dbc);
	u32	dsa	= INL(np, nc_dsa);
	u_char	sbcl	= INB(np, nc_sbcl);
	u_char	cmd	= dbc >> 24;
	int phase	= cmd & 7;
	struct sym_ccb *cp	= sym_ccb_from_dsa(np, dsa);

	if (printk_ratelimit())
		printf("%s: SCSI parity error detected: SCR1=%d DBC=%x SBCL=%x\n",
			sym_name(np), hsts, dbc, sbcl);

	/*
	 *  Check that the chip is connected to the SCSI BUS.
	 */
	if (!(INB(np, nc_scntl1) & ISCON)) {
		sym_recover_scsi_int(np, HS_UNEXPECTED);
		return;
	}

	/*
	 *  If the nexus is not clearly identified, reset the bus.
	 *  We will try to do better later.
	 */
	if (!cp)
		goto reset_all;

	/*
	 *  Check instruction was a MOV, direction was INPUT and 
	 *  ATN is asserted.
	 */
	if ((cmd & 0xc0) || !(phase & 1) || !(sbcl & 0x8))
		goto reset_all;

	/*
	 *  Keep track of the parity error.
	 */
	OUTONB(np, HF_PRT, HF_EXT_ERR);
	cp->xerr_status |= XE_PARITY_ERR;

	/*
	 *  Prepare the message to send to the device.
	 */
	np->msgout[0] = (phase == 7) ? M_PARITY : M_ID_ERROR;

	/*
	 *  If the old phase was DATA IN phase, we have to deal with
	 *  the 3 situations described above.
	 *  For other input phases (MSG IN and STATUS), the device 
	 *  must resend the whole thing that failed parity checking 
	 *  or signal error. So, jumping to dispatcher should be OK.
	 */
	if (phase == 1 || phase == 5) {
		/* Phase mismatch handled by SCRIPTS */
		if (dsp == SCRIPTB_BA(np, pm_handle))
			OUTL_DSP(np, dsp);
		/* Phase mismatch handled by the C code */
		else if (sist & MA)
			sym_int_ma (np);
		/* No phase mismatch occurred */
		else {
			sym_set_script_dp (np, cp, dsp);
			OUTL_DSP(np, SCRIPTA_BA(np, dispatch));
		}
	}
	else if (phase == 7)	/* We definitely cannot handle parity errors */
#if 1				/* in message-in phase due to the relection  */
		goto reset_all; /* path and various message anticipations.   */
#else
		OUTL_DSP(np, SCRIPTA_BA(np, clrack));
#endif
	else
		OUTL_DSP(np, SCRIPTA_BA(np, dispatch));
	return;

reset_all:
	sym_start_reset(np);
	return;
}