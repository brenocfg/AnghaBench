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
 int /*<<< orphan*/  SM_DATAIO ; 
 int /*<<< orphan*/  SM_REGINDEX ; 
 unsigned int SM_WATCHTIMER ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supermicro_new_lock_watchdog () ; 
 int /*<<< orphan*/  supermicro_new_unlock_watchdog () ; 

__attribute__((used)) static void supermicro_new_pre_set_heartbeat(unsigned int heartbeat)
{
	supermicro_new_unlock_watchdog();

	/* reset watchdog timeout to heartveat value */
	outb(SM_WATCHTIMER, SM_REGINDEX);
	outb((heartbeat & 255), SM_DATAIO);

	supermicro_new_lock_watchdog();
}