#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  cd_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDROM_COM_EXECDIAG ; 
 int /*<<< orphan*/  GDROM_ERROR_REG ; 
 int /*<<< orphan*/  GDROM_STATUSCOMMAND_REG ; 
 char ctrl_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ gd ; 
 int /*<<< orphan*/  gdrom_hardreset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdrom_wait_busy_sleeps () ; 
 int /*<<< orphan*/  gdrom_wait_clrbusy () ; 

__attribute__((used)) static char gdrom_execute_diagnostic(void)
{
	gdrom_hardreset(gd.cd_info);
	if (!gdrom_wait_clrbusy())
		return 0;
	ctrl_outb(GDROM_COM_EXECDIAG, GDROM_STATUSCOMMAND_REG);
	if (!gdrom_wait_busy_sleeps())
		return 0;
	return ctrl_inb(GDROM_ERROR_REG);
}