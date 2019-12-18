#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int enable; int full_screen; } ;
struct TYPE_6__ {TYPE_2__ frame; TYPE_1__ texture; } ;
typedef  TYPE_3__ thread_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thread_set_texture_enable(void *data, bool state, bool full_screen)
{
   thread_video_t *thr = (thread_video_t*)data;
   if (!thr)
      return;

   slock_lock(thr->frame.lock);
   thr->texture.enable      = state;
   thr->texture.full_screen = full_screen;
   slock_unlock(thr->frame.lock);
}