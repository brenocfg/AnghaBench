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
 int /*<<< orphan*/  GDROM_ALTSTATUS_REG ; 
 unsigned long GDROM_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int ctrl_inb (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static bool gdrom_wait_clrbusy(void)
{
	unsigned long timeout = jiffies + GDROM_DEFAULT_TIMEOUT;
	while ((ctrl_inb(GDROM_ALTSTATUS_REG) & 0x80) &&
		(time_before(jiffies, timeout)))
		cpu_relax();
	return time_before(jiffies, timeout + 1);
}