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
struct TYPE_2__ {int has_windowed; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ thread_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool video_thread_has_windowed(void *data)
{
   bool ret;
   thread_video_t *thr = (thread_video_t*)data;

   slock_lock(thr->lock);
   ret = thr->has_windowed;
   slock_unlock(thr->lock);

   return ret;
}