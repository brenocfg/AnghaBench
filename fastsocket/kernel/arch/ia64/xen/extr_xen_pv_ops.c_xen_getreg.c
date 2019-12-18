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
#define  _IA64_REG_AR_EFLAG 133 
#define  _IA64_REG_AR_ITC 132 
#define  _IA64_REG_CR_ITM 131 
#define  _IA64_REG_CR_IVR 130 
#define  _IA64_REG_CR_TPR 129 
#define  _IA64_REG_PSR 128 
 unsigned long ia64_native_getreg_func (int) ; 
 unsigned long xen_get_eflag () ; 
 unsigned long xen_get_itc () ; 
 unsigned long xen_get_itm_with_offset () ; 
 unsigned long xen_get_ivr () ; 
 unsigned long xen_get_psr () ; 
 unsigned long xen_get_tpr () ; 

__attribute__((used)) static unsigned long xen_getreg(int regnum)
{
	unsigned long res;

	switch (regnum) {
	case _IA64_REG_PSR:
		res = xen_get_psr();
		break;
#ifdef CONFIG_IA32_SUPPORT
	case _IA64_REG_AR_EFLAG:
		res = xen_get_eflag();
		break;
#endif
	case _IA64_REG_AR_ITC:
		res = xen_get_itc();
		break;
	case _IA64_REG_CR_ITM:
		res = xen_get_itm_with_offset();
		break;
	case _IA64_REG_CR_IVR:
		res = xen_get_ivr();
		break;
	case _IA64_REG_CR_TPR:
		res = xen_get_tpr();
		break;
	default:
		res = ia64_native_getreg_func(regnum);
		break;
	}
	return res;
}