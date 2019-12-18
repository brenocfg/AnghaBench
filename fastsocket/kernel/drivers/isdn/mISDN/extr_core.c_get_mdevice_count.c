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
 int /*<<< orphan*/  _get_mdevice_count ; 
 int /*<<< orphan*/  class_for_each_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mISDN_class ; 

int
get_mdevice_count(void)
{
	int cnt = 0;

	class_for_each_device(&mISDN_class, NULL, &cnt, _get_mdevice_count);
	return cnt;
}