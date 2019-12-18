#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int refresh_rate; } ;
typedef  TYPE_5__ video_frame_info_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {int updated; unsigned int width; unsigned int height; unsigned int pitch; char* msg; int /*<<< orphan*/  count; int /*<<< orphan*/ * buffer; scalar_t__ within_thread; } ;
struct TYPE_12__ {scalar_t__ enable; } ;
struct TYPE_11__ {scalar_t__ rgb32; } ;
struct TYPE_15__ {scalar_t__ last_time; int /*<<< orphan*/  lock; int /*<<< orphan*/  miss_count; int /*<<< orphan*/  hit_count; int /*<<< orphan*/  cond_cmd; TYPE_4__ frame; TYPE_3__ texture; int /*<<< orphan*/  cond_thread; int /*<<< orphan*/  nonblock; TYPE_2__ info; int /*<<< orphan*/  driver_data; TYPE_1__* driver; } ;
typedef  TYPE_6__ thread_video_t ;
typedef  scalar_t__ retro_time_t ;
struct TYPE_10__ {int (* frame ) (int /*<<< orphan*/ ,void const*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,char const*,TYPE_5__*) ;} ;

/* Variables and functions */
 scalar_t__ cpu_features_get_time_usec () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  roundf (int) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int stub1 (int /*<<< orphan*/ ,void const*,unsigned int,unsigned int,int /*<<< orphan*/ ,unsigned int,char const*,TYPE_5__*) ; 
 int /*<<< orphan*/  thread_update_driver_state (TYPE_6__*) ; 

__attribute__((used)) static bool video_thread_frame(void *data, const void *frame_,
      unsigned width, unsigned height, uint64_t frame_count,
      unsigned pitch, const char *msg, video_frame_info_t *video_info)
{
   unsigned copy_stride;
   const uint8_t *src                  = NULL;
   uint8_t *dst                        = NULL;
   thread_video_t *thr                 = (thread_video_t*)data;

   /* If called from within read_viewport, we're actually in the
    * driver thread, so just render directly. */
   if (thr->frame.within_thread)
   {
      thread_update_driver_state(thr);

      if (thr->driver && thr->driver->frame)
         return thr->driver->frame(thr->driver_data, frame_,
               width, height, frame_count, pitch, msg, video_info);
      return false;
   }

   copy_stride = width * (thr->info.rgb32
         ? sizeof(uint32_t) : sizeof(uint16_t));

   src = (const uint8_t*)frame_;
   dst = thr->frame.buffer;

   slock_lock(thr->lock);

   if (!thr->nonblock)
   {

      retro_time_t target_frame_time = (retro_time_t)
         roundf(1000000 / video_info->refresh_rate);
      retro_time_t target = thr->last_time + target_frame_time;

      /* Ideally, use absolute time, but that is only a good idea on POSIX. */
      while (thr->frame.updated)
      {
         retro_time_t current = cpu_features_get_time_usec();
         retro_time_t delta   = target - current;

         if (delta <= 0)
            break;

         if (!scond_wait_timeout(thr->cond_cmd, thr->lock, delta))
            break;
      }
   }

   /* Drop frame if updated flag is still set, as thread is
    * still working on last frame. */
   if (!thr->frame.updated)
   {
      if (src)
      {
         unsigned h;
         for (h = 0; h < height; h++, src += pitch, dst += copy_stride)
            memcpy(dst, src, copy_stride);
      }

      thr->frame.updated = true;
      thr->frame.width  = width;
      thr->frame.height = height;
      thr->frame.count  = frame_count;
      thr->frame.pitch  = copy_stride;

      if (msg)
         strlcpy(thr->frame.msg, msg, sizeof(thr->frame.msg));
      else
         *thr->frame.msg = '\0';

      scond_signal(thr->cond_thread);

#if defined(HAVE_MENU)
      if (thr->texture.enable)
      {
         while (thr->frame.updated)
            scond_wait(thr->cond_cmd, thr->lock);
      }
#endif
      thr->hit_count++;
   }
   else
      thr->miss_count++;

   slock_unlock(thr->lock);

   thr->last_time = cpu_features_get_time_usec();
   return true;
}