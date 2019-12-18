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
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int /*<<< orphan*/  jogdial; int /*<<< orphan*/  wireless; } ;

/* Variables and functions */
 int /*<<< orphan*/  TC1100_INSTANCE_JOGDIAL ; 
 int /*<<< orphan*/  TC1100_INSTANCE_WIRELESS ; 
 int get_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ suspend_data ; 

__attribute__((used)) static int tc1100_suspend(struct platform_device *dev, pm_message_t state)
{
	int ret;

	ret = get_state(&suspend_data.wireless, TC1100_INSTANCE_WIRELESS);
	if (ret)
		return ret;

	ret = get_state(&suspend_data.jogdial, TC1100_INSTANCE_JOGDIAL);
	if (ret)
		return ret;

	return ret;
}