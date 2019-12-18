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
struct smm_regs {int eax; } ;

/* Variables and functions */
#define  I8K_FN_DOWN 130 
 int I8K_FN_MASK ; 
#define  I8K_FN_MUTE 129 
 int I8K_FN_SHIFT ; 
#define  I8K_FN_UP 128 
 int I8K_SMM_FN_STATUS ; 
 int I8K_VOL_DOWN ; 
 int I8K_VOL_MUTE ; 
 int I8K_VOL_UP ; 
 int i8k_smm (struct smm_regs*) ; 

__attribute__((used)) static int i8k_get_fn_status(void)
{
	struct smm_regs regs = { .eax = I8K_SMM_FN_STATUS, };
	int rc;

	if ((rc = i8k_smm(&regs)) < 0)
		return rc;

	switch ((regs.eax >> I8K_FN_SHIFT) & I8K_FN_MASK) {
	case I8K_FN_UP:
		return I8K_VOL_UP;
	case I8K_FN_DOWN:
		return I8K_VOL_DOWN;
	case I8K_FN_MUTE:
		return I8K_VOL_MUTE;
	default:
		return 0;
	}
}