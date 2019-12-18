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
 int /*<<< orphan*/  AT91_ST_EXTEN ; 
 int /*<<< orphan*/  AT91_ST_WDMR ; 
 int /*<<< orphan*/  at91_sys_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void at91_wdt_stop(void)
{
	at91_sys_write(AT91_ST_WDMR, AT91_ST_EXTEN);
}