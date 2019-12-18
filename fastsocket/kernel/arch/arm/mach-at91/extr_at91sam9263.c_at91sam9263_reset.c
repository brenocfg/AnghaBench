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
 int /*<<< orphan*/  AT91_RSTC_CR ; 
 int AT91_RSTC_KEY ; 
 int AT91_RSTC_PERRST ; 
 int AT91_RSTC_PROCRST ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91sam9263_reset(void)
{
	at91_sys_write(AT91_RSTC_CR, AT91_RSTC_KEY | AT91_RSTC_PROCRST | AT91_RSTC_PERRST);
}