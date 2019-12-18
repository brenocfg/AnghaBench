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
typedef  int u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INST_CPRT (int) ; 
 scalar_t__ INST_CPRTDO (int) ; 
 int VFP_EXCEPTION_ERROR ; 
 int VFP_NAN_FLAG ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 
 int vfp_double_cpdo (int,int) ; 
 scalar_t__ vfp_single (int) ; 
 int vfp_single_cpdo (int,int) ; 

__attribute__((used)) static u32 vfp_emulate_instruction(u32 inst, u32 fpscr, struct pt_regs *regs)
{
	u32 exceptions = VFP_EXCEPTION_ERROR;

	pr_debug("VFP: emulate: INST=0x%08x SCR=0x%08x\n", inst, fpscr);

	if (INST_CPRTDO(inst)) {
		if (!INST_CPRT(inst)) {
			/*
			 * CPDO
			 */
			if (vfp_single(inst)) {
				exceptions = vfp_single_cpdo(inst, fpscr);
			} else {
				exceptions = vfp_double_cpdo(inst, fpscr);
			}
		} else {
			/*
			 * A CPRT instruction can not appear in FPINST2, nor
			 * can it cause an exception.  Therefore, we do not
			 * have to emulate it.
			 */
		}
	} else {
		/*
		 * A CPDT instruction can not appear in FPINST2, nor can
		 * it cause an exception.  Therefore, we do not have to
		 * emulate it.
		 */
	}
	return exceptions & ~VFP_NAN_FLAG;
}