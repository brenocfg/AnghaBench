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
struct work_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  expires_work ; 
 int /*<<< orphan*/  ip_rt_gc_interval ; 
 int /*<<< orphan*/  rt_check_expire () ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt_worker_func(struct work_struct *work)
{
	rt_check_expire();
	schedule_delayed_work(&expires_work, ip_rt_gc_interval);
}