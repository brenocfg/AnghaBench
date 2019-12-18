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
typedef  scalar_t__ u32 ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_CKGR_PLLBR ; 
 int AT91_PMC_LOCKB ; 
 int /*<<< orphan*/  AT91_PMC_SR ; 
 scalar_t__ at91_pllb_usb_init ; 
 int at91_sys_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  cpu_relax () ; 

__attribute__((used)) static void pllb_mode(struct clk *clk, int is_on)
{
	u32	value;

	if (is_on) {
		is_on = AT91_PMC_LOCKB;
		value = at91_pllb_usb_init;
	} else
		value = 0;

	// REVISIT: Add work-around for AT91RM9200 Errata #26 ?
	at91_sys_write(AT91_CKGR_PLLBR, value);

	do {
		cpu_relax();
	} while ((at91_sys_read(AT91_PMC_SR) & AT91_PMC_LOCKB) != is_on);
}