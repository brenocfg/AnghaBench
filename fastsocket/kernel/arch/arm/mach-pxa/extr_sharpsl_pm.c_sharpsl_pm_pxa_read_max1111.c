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
 int MAXCTRL_PD0 ; 
 int MAXCTRL_PD1 ; 
 int MAXCTRL_SEL_SH ; 
 int MAXCTRL_SGL ; 
 int MAXCTRL_STR ; 
 int MAXCTRL_UNI ; 
 int corgi_ssp_max1111_get (int) ; 
 scalar_t__ machine_is_tosa () ; 

int sharpsl_pm_pxa_read_max1111(int channel)
{
	if (machine_is_tosa()) // Ugly, better move this function into another module
	    return 0;

#ifdef CONFIG_CORGI_SSP_DEPRECATED
	return corgi_ssp_max1111_get((channel << MAXCTRL_SEL_SH) | MAXCTRL_PD0 | MAXCTRL_PD1
			| MAXCTRL_SGL | MAXCTRL_UNI | MAXCTRL_STR);
#else
	extern int max1111_read_channel(int);

	/* max1111 accepts channels from 0-3, however,
	 * it is encoded from 0-7 here in the code.
	 */
	return max1111_read_channel(channel >> 1);
#endif
}