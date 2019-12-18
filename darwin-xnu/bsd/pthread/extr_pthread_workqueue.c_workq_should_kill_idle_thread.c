#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct workqueue {int dummy; } ;
struct TYPE_3__ {scalar_t__ idle_stamp; } ;
struct TYPE_4__ {TYPE_1__ uus_workq_park_data; } ;
struct uthread {TYPE_2__ uu_save; } ;

/* Variables and functions */
 scalar_t__ workq_kill_delay_for_idle_thread (struct workqueue*) ; 

__attribute__((used)) static inline bool
workq_should_kill_idle_thread(struct workqueue *wq, struct uthread *uth,
		uint64_t now)
{
	uint64_t delay = workq_kill_delay_for_idle_thread(wq);
	return now - uth->uu_save.uus_workq_park_data.idle_stamp > delay;
}