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
 int /*<<< orphan*/  DBG (char*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  FAN_CTRLER_ID ; 
 int /*<<< orphan*/ * attach_i2c_chip (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fcu ; 

__attribute__((used)) static int attach_fcu(void)
{
	fcu = attach_i2c_chip(FAN_CTRLER_ID, "fcu");
	if (fcu == NULL)
		return -ENODEV;

	DBG("FCU attached\n");

	return 0;
}