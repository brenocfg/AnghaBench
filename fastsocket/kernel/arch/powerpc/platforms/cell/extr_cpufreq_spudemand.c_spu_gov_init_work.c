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
struct spu_gov_info_struct {int /*<<< orphan*/  work; TYPE_1__* policy; int /*<<< orphan*/  poll_int; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK_DEFERRABLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kspugov_wq ; 
 int /*<<< orphan*/  queue_delayed_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spu_gov_work ; 
 int usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void spu_gov_init_work(struct spu_gov_info_struct *info)
{
	int delay = usecs_to_jiffies(info->poll_int);
	INIT_DELAYED_WORK_DEFERRABLE(&info->work, spu_gov_work);
	queue_delayed_work_on(info->policy->cpu, kspugov_wq, &info->work, delay);
}