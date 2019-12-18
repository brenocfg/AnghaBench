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
struct TYPE_3__ {int alive; int can_sleep; int /*<<< orphan*/ * thread; int /*<<< orphan*/  cond; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ffmpeg_t ;

/* Variables and functions */
 int /*<<< orphan*/  scond_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sthread_join (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deinit_thread(ffmpeg_t *handle)
{
   if (!handle->thread)
      return;

   slock_lock(handle->cond_lock);
   handle->alive = false;
   handle->can_sleep = false;
   slock_unlock(handle->cond_lock);

   scond_signal(handle->cond);
   sthread_join(handle->thread);

   slock_free(handle->lock);
   slock_free(handle->cond_lock);
   scond_free(handle->cond);

   handle->thread = NULL;
}