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
 int /*<<< orphan*/  DEFAULT_TIMER_EXPIRE ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ spu_prof_running ; 
 int /*<<< orphan*/  spu_work ; 
 int /*<<< orphan*/  sync_spu_buff () ; 

__attribute__((used)) static void wq_sync_spu_buff(struct work_struct *work)
{
	/* move data from spu buffers to kernel buffer */
	sync_spu_buff();

	/* only reschedule if profiling is not done */
	if (spu_prof_running)
		schedule_delayed_work(&spu_work, DEFAULT_TIMER_EXPIRE);
}