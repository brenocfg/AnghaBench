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
typedef  struct record_video_data {unsigned int width; unsigned int height; unsigned int pitch; scalar_t__ data; scalar_t__ is_dupe; } const record_video_data ;
typedef  struct record_video_data uint8_t ;
struct TYPE_3__ {int frame_drop_count; int frame_drop_ratio; int pix_size; } ;
struct TYPE_4__ {int can_sleep; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; int /*<<< orphan*/  video_fifo; int /*<<< orphan*/  attr_fifo; TYPE_1__ video; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  alive; } ;
typedef  TYPE_2__ ffmpeg_t ;
typedef  int /*<<< orphan*/  attr_data ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,struct record_video_data const*,int) ; 
 unsigned int fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ffmpeg_push_video(void *data,
      const struct record_video_data *vid)
{
   unsigned y;
   bool drop_frame;
   struct record_video_data attr_data;
   ffmpeg_t *handle = (ffmpeg_t*)data;
   int       offset = 0;

   if (!handle || !vid)
      return false;

   drop_frame = handle->video.frame_drop_count++ %
      handle->video.frame_drop_ratio;

   handle->video.frame_drop_count %= handle->video.frame_drop_ratio;

   if (drop_frame)
      return true;

   for (;;)
   {
      unsigned avail;
      slock_lock(handle->lock);
      avail = fifo_write_avail(handle->attr_fifo);
      slock_unlock(handle->lock);

      if (!handle->alive)
         return false;

      if (avail >= sizeof(*vid))
         break;

      slock_lock(handle->cond_lock);
      if (handle->can_sleep)
      {
         handle->can_sleep = false;
         scond_wait(handle->cond, handle->cond_lock);
         handle->can_sleep = true;
      }
      else
         scond_signal(handle->cond);

      slock_unlock(handle->cond_lock);
   }

   slock_lock(handle->lock);

   /* Tightly pack our frame to conserve memory.
    * libretro tends to use a very large pitch.
    */
   attr_data = *vid;

   if (attr_data.is_dupe)
      attr_data.width = attr_data.height = attr_data.pitch = 0;
   else
      attr_data.pitch = attr_data.width * handle->video.pix_size;

   fifo_write(handle->attr_fifo, &attr_data, sizeof(attr_data));

   for (y = 0; y < attr_data.height; y++, offset += vid->pitch)
      fifo_write(handle->video_fifo,
            (const uint8_t*)vid->data + offset, attr_data.pitch);

   slock_unlock(handle->lock);
   scond_signal(handle->cond);

   return true;
}