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
struct fsl_upm {int width; int /*<<< orphan*/ * mxmr; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  mcmr; int /*<<< orphan*/  mbmr; int /*<<< orphan*/  mamr; TYPE_1__* bank; } ;
struct TYPE_3__ {int /*<<< orphan*/  br; } ;

/* Variables and functions */
 int BR_MSEL ; 
#define  BR_MS_UPMA 133 
#define  BR_MS_UPMB 132 
#define  BR_MS_UPMC 131 
 int BR_PS ; 
#define  BR_PS_16 130 
#define  BR_PS_32 129 
#define  BR_PS_8 128 
 int EINVAL ; 
 int fsl_lbc_find (int /*<<< orphan*/ ) ; 
 TYPE_2__* fsl_lbc_regs ; 
 int in_be32 (int /*<<< orphan*/ *) ; 

int fsl_upm_find(phys_addr_t addr_base, struct fsl_upm *upm)
{
	int bank;
	__be32 br;

	bank = fsl_lbc_find(addr_base);
	if (bank < 0)
		return bank;

	br = in_be32(&fsl_lbc_regs->bank[bank].br);

	switch (br & BR_MSEL) {
	case BR_MS_UPMA:
		upm->mxmr = &fsl_lbc_regs->mamr;
		break;
	case BR_MS_UPMB:
		upm->mxmr = &fsl_lbc_regs->mbmr;
		break;
	case BR_MS_UPMC:
		upm->mxmr = &fsl_lbc_regs->mcmr;
		break;
	default:
		return -EINVAL;
	}

	switch (br & BR_PS) {
	case BR_PS_8:
		upm->width = 8;
		break;
	case BR_PS_16:
		upm->width = 16;
		break;
	case BR_PS_32:
		upm->width = 32;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}