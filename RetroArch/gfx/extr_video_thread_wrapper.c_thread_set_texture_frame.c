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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {size_t frame_cap; int frame_updated; int rgb32; unsigned int width; unsigned int height; float alpha; scalar_t__ frame; } ;
struct TYPE_6__ {TYPE_2__ frame; TYPE_1__ texture; } ;
typedef  TYPE_3__ thread_video_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 scalar_t__ realloc (scalar_t__,size_t) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void thread_set_texture_frame(void *data, const void *frame,
      bool rgb32, unsigned width, unsigned height, float alpha)
{
   thread_video_t *thr = (thread_video_t*)data;
   size_t required     = width * height *
      (rgb32 ? sizeof(uint32_t) : sizeof(uint16_t));

   slock_lock(thr->frame.lock);

   if (required > thr->texture.frame_cap)
   {
      thr->texture.frame     = realloc(thr->texture.frame, required);
      thr->texture.frame_cap = required;
   }

   if (thr->texture.frame)
   {
      memcpy(thr->texture.frame, frame, required);
      thr->texture.frame_updated = true;
      thr->texture.rgb32         = rgb32;
      thr->texture.width         = width;
      thr->texture.height        = height;
      thr->texture.alpha         = alpha;
   }
   slock_unlock(thr->frame.lock);
}