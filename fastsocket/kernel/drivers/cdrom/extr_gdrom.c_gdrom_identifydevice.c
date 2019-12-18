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
 int /*<<< orphan*/  GDROM_COM_IDDEV ; 
 int /*<<< orphan*/  GDROM_DATA_REG ; 
 int /*<<< orphan*/  GDROM_STATUSCOMMAND_REG ; 
 short ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdrom_getsense (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdrom_wait_busy_sleeps () ; 
 int /*<<< orphan*/  gdrom_wait_clrbusy () ; 

__attribute__((used)) static void gdrom_identifydevice(void *buf)
{
	int c;
	short *data = buf;
	/* If the device won't clear it has probably
	* been hit by a serious failure - but we'll
	* try to return a sense key even so */
	if (!gdrom_wait_clrbusy()) {
		gdrom_getsense(NULL);
		return;
	}
	ctrl_outb(GDROM_COM_IDDEV, GDROM_STATUSCOMMAND_REG);
	if (!gdrom_wait_busy_sleeps()) {
		gdrom_getsense(NULL);
		return;
	}
	/* now read in the data */
	for (c = 0; c < 40; c++)
		data[c] = ctrl_inw(GDROM_DATA_REG);
}