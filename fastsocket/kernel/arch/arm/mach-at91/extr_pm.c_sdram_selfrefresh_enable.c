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

/* Variables and functions */
 int AT91_SDRAMC_LPCB ; 
 int AT91_SDRAMC_LPCB_SELF_REFRESH ; 
 int /*<<< orphan*/  AT91_SDRAMC_LPR ; 
 int at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int) ; 
 int saved_lpr ; 

__attribute__((used)) static inline void sdram_selfrefresh_enable(void)
{
	u32 lpr;

	saved_lpr = at91_sys_read(AT91_SDRAMC_LPR);

	lpr = saved_lpr & ~AT91_SDRAMC_LPCB;
	at91_sys_write(AT91_SDRAMC_LPR, lpr | AT91_SDRAMC_LPCB_SELF_REFRESH);
}