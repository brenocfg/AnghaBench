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

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  IOP13XX_ESSR0 ; 
#define  IOP13XX_INIT_ATU_ATUE 129 
#define  IOP13XX_INIT_ATU_ATUX 128 
 int IOP13XX_INTERFACE_SEL_PCIX ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iop13xx_atu_function(int atu)
{
	int func = 0;
	/* the function number depends on the value of the
	 * IOP13XX_INTERFACE_SEL_PCIX reset strap
	 * see C-Spec section 3.17
	 */
	switch(atu) {
	case IOP13XX_INIT_ATU_ATUX:
		if (__raw_readl(IOP13XX_ESSR0) & IOP13XX_INTERFACE_SEL_PCIX)
			func = 5;
		else
			func = 0;
		break;
	case IOP13XX_INIT_ATU_ATUE:
		if (__raw_readl(IOP13XX_ESSR0) & IOP13XX_INTERFACE_SEL_PCIX)
			func = 0;
		else
			func = 5;
		break;
	default:
		BUG();
	}

	return func;
}