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
struct video_viewport {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct video_viewport vp; int /*<<< orphan*/  read_vp; } ;
typedef  TYPE_1__ thread_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct video_viewport*,int) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void video_thread_viewport_info(void *data, struct video_viewport *vp)
{
   thread_video_t *thr = (thread_video_t*)data;

   if (!thr)
      return;

   slock_lock(thr->lock);
   *vp = thr->vp;

   /* Explicitly mem-copied so we can use memcmp correctly later. */
   memcpy(&thr->read_vp, &thr->vp, sizeof(thr->vp));
   slock_unlock(thr->lock);
}