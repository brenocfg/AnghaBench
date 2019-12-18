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
 int ctrl_inb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool gdrom_is_busy(void)
{
	return (ctrl_inb(GDROM_ALTSTATUS_REG) & 0x80) != 0;
}