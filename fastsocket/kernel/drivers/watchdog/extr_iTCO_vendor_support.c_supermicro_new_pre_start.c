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
 unsigned int SM_COUNTMODE ; 
 int /*<<< orphan*/  SM_DATAIO ; 
 int /*<<< orphan*/  SM_REGINDEX ; 
 unsigned int SM_RESETCONTROL ; 
 unsigned int SM_WATCHENABLE ; 
 unsigned int SM_WATCHTIMER ; 
 unsigned int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supermicro_new_lock_watchdog () ; 
 int /*<<< orphan*/  supermicro_new_unlock_watchdog () ; 

__attribute__((used)) static void supermicro_new_pre_start(unsigned int heartbeat)
{
	unsigned int val;

	supermicro_new_unlock_watchdog();

	/* Watchdog timer setting needs to be in seconds*/
	outb(SM_COUNTMODE, SM_REGINDEX);
	val = inb(SM_DATAIO);
	val &= 0xF7;
	outb(val, SM_DATAIO);

	/* Write heartbeat interval to WDOG */
	outb(SM_WATCHTIMER, SM_REGINDEX);
	outb((heartbeat & 255), SM_DATAIO);

	/* Make sure keyboard/mouse interrupts don't interfere */
	outb(SM_RESETCONTROL, SM_REGINDEX);
	val = inb(SM_DATAIO);
	val &= 0x3f;
	outb(val, SM_DATAIO);

	/* enable watchdog by setting bit 0 of Watchdog Enable to 1 */
	outb(SM_WATCHENABLE, SM_REGINDEX);
	val = inb(SM_DATAIO);
	val |= 0x01;
	outb(val, SM_DATAIO);

	supermicro_new_lock_watchdog();
}