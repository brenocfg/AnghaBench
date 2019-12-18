#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tlbsize; } ;
struct TYPE_3__ {int tlbsize; } ;

/* Variables and functions */
 int MAX_SMTC_ASIDS ; 
 int MAX_SMTC_TLBS ; 
 int MIPS_CONF_MT ; 
 unsigned long MVPCONF0_PTLBE ; 
 unsigned long MVPCONF0_PTLBE_SHIFT ; 
 unsigned long MVPCONF0_PVPE ; 
 unsigned long MVPCONF0_PVPE_SHIFT ; 
 unsigned long MVPCONF0_TLBS ; 
 int MVPCONTROL_STLB ; 
 int MVPCONTROL_VPC ; 
 int /*<<< orphan*/  SMTC_TLB_SHARED ; 
 int /*<<< orphan*/  TCHALT_H ; 
 TYPE_2__* cpu_data ; 
 TYPE_1__ current_cpu_data ; 
 int /*<<< orphan*/  ehb () ; 
 int /*<<< orphan*/  local_flush_tlb_all () ; 
 int /*<<< orphan*/  mips_ihb () ; 
 int /*<<< orphan*/  nostlb ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 unsigned long read_c0_mvpconf0 () ; 
 int read_c0_mvpcontrol () ; 
 int read_vpe_c0_config () ; 
 unsigned long read_vpe_c0_config1 () ; 
 int /*<<< orphan*/  settc (int) ; 
 scalar_t__** smtc_live_asid ; 
 int /*<<< orphan*/  smtc_status ; 
 int /*<<< orphan*/  write_c0_mvpcontrol (int) ; 
 int /*<<< orphan*/  write_tc_c0_tcbind (int) ; 
 int /*<<< orphan*/  write_tc_c0_tchalt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void smtc_configure_tlb(void)
{
	int i, tlbsiz, vpes;
	unsigned long mvpconf0;
	unsigned long config1val;

	/* Set up ASID preservation table */
	for (vpes=0; vpes<MAX_SMTC_TLBS; vpes++) {
	    for(i = 0; i < MAX_SMTC_ASIDS; i++) {
		smtc_live_asid[vpes][i] = 0;
	    }
	}
	mvpconf0 = read_c0_mvpconf0();

	if ((vpes = ((mvpconf0 & MVPCONF0_PVPE)
			>> MVPCONF0_PVPE_SHIFT) + 1) > 1) {
	    /* If we have multiple VPEs, try to share the TLB */
	    if ((mvpconf0 & MVPCONF0_TLBS) && !nostlb) {
		/*
		 * If TLB sizing is programmable, shared TLB
		 * size is the total available complement.
		 * Otherwise, we have to take the sum of all
		 * static VPE TLB entries.
		 */
		if ((tlbsiz = ((mvpconf0 & MVPCONF0_PTLBE)
				>> MVPCONF0_PTLBE_SHIFT)) == 0) {
		    /*
		     * If there's more than one VPE, there had better
		     * be more than one TC, because we need one to bind
		     * to each VPE in turn to be able to read
		     * its configuration state!
		     */
		    settc(1);
		    /* Stop the TC from doing anything foolish */
		    write_tc_c0_tchalt(TCHALT_H);
		    mips_ihb();
		    /* No need to un-Halt - that happens later anyway */
		    for (i=0; i < vpes; i++) {
		    	write_tc_c0_tcbind(i);
			/*
			 * To be 100% sure we're really getting the right
			 * information, we exit the configuration state
			 * and do an IHB after each rebinding.
			 */
			write_c0_mvpcontrol(
				read_c0_mvpcontrol() & ~ MVPCONTROL_VPC );
			mips_ihb();
			/*
			 * Only count if the MMU Type indicated is TLB
			 */
			if (((read_vpe_c0_config() & MIPS_CONF_MT) >> 7) == 1) {
				config1val = read_vpe_c0_config1();
				tlbsiz += ((config1val >> 25) & 0x3f) + 1;
			}

			/* Put core back in configuration state */
			write_c0_mvpcontrol(
				read_c0_mvpcontrol() | MVPCONTROL_VPC );
			mips_ihb();
		    }
		}
		write_c0_mvpcontrol(read_c0_mvpcontrol() | MVPCONTROL_STLB);
		ehb();

		/*
		 * Setup kernel data structures to use software total,
		 * rather than read the per-VPE Config1 value. The values
		 * for "CPU 0" gets copied to all the other CPUs as part
		 * of their initialization in smtc_cpu_setup().
		 */

		/* MIPS32 limits TLB indices to 64 */
		if (tlbsiz > 64)
			tlbsiz = 64;
		cpu_data[0].tlbsize = current_cpu_data.tlbsize = tlbsiz;
		smtc_status |= SMTC_TLB_SHARED;
		local_flush_tlb_all();

		printk("TLB of %d entry pairs shared by %d VPEs\n",
			tlbsiz, vpes);
	    } else {
		printk("WARNING: TLB Not Sharable on SMTC Boot!\n");
	    }
	}
}