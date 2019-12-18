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
struct i1480 {int /*<<< orphan*/  pre_fw_name; } ;

/* Variables and functions */
 int __mac_fw_upload (struct i1480*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

int i1480_pre_fw_upload(struct i1480 *i1480)
{
	int result;
	result = __mac_fw_upload(i1480, i1480->pre_fw_name, "PRE");
	if (result == 0)
		msleep(400);
	return result;
}