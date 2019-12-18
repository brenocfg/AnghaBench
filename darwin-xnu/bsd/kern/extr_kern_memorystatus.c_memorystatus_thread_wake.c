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
typedef  int /*<<< orphan*/  event_t ;
struct TYPE_2__ {int /*<<< orphan*/  memorystatus_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  active_jetsam_threads ; 
 int atomic_load (int /*<<< orphan*/ *) ; 
 TYPE_1__* jetsam_threads ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
memorystatus_thread_wake(void)
{      
	int thr_id = 0;
	int active_thr = atomic_load(&active_jetsam_threads);

	/* Wakeup all the jetsam threads */
	for (thr_id = 0; thr_id < active_thr; thr_id++) {
		thread_wakeup((event_t)&jetsam_threads[thr_id].memorystatus_wakeup); 
	}       
}