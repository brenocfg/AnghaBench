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
 int /*<<< orphan*/  AT91_SHDW_CR ; 
 int AT91_SHDW_KEY ; 
 int AT91_SHDW_SHDW ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91sam9260_poweroff(void)
{
	at91_sys_write(AT91_SHDW_CR, AT91_SHDW_KEY | AT91_SHDW_SHDW);
}