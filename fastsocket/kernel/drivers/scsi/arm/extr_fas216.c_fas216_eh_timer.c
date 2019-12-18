#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rst_bus_status; int rst_dev_status; int /*<<< orphan*/  eh_wait; int /*<<< orphan*/  eh_timer; } ;
typedef  TYPE_1__ FAS216_Info ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fas216_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fas216_eh_timer(unsigned long data)
{
	FAS216_Info *info = (FAS216_Info *)data;

	fas216_log(info, LOG_ERROR, "error handling timed out\n");

	del_timer(&info->eh_timer);

	if (info->rst_bus_status == 0)
		info->rst_bus_status = -1;
	if (info->rst_dev_status == 0)
		info->rst_dev_status = -1;

	wake_up(&info->eh_wait);
}