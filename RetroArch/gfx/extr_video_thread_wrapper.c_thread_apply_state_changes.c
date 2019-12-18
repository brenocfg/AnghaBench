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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int apply_state_changes; TYPE_1__ frame; } ;
typedef  TYPE_2__ thread_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thread_apply_state_changes(void *data)
{
   thread_video_t *thr = (thread_video_t*)data;

   if (!thr)
      return;

   slock_lock(thr->frame.lock);
   thr->apply_state_changes = true;
   slock_unlock(thr->frame.lock);
}