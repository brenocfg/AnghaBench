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
struct record_audio_data {int frames; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_5__ {int channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  audio_enable; } ;
struct TYPE_6__ {int can_sleep; int /*<<< orphan*/  cond; int /*<<< orphan*/  lock; TYPE_2__ params; int /*<<< orphan*/  audio_fifo; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  alive; TYPE_1__ config; } ;
typedef  TYPE_3__ ffmpeg_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 unsigned int fifo_write_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ffmpeg_push_audio(void *data,
      const struct record_audio_data *audio_data)
{
   ffmpeg_t *handle = (ffmpeg_t*)data;

   if (!handle || !audio_data)
      return false;

   if (!handle->config.audio_enable)
      return true;

   for (;;)
   {
      unsigned avail;
      slock_lock(handle->lock);
      avail = fifo_write_avail(handle->audio_fifo);
      slock_unlock(handle->lock);

      if (!handle->alive)
         return false;

      if (avail >= audio_data->frames * handle->params.channels
            * sizeof(int16_t))
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
   fifo_write(handle->audio_fifo, audio_data->data,
         audio_data->frames * handle->params.channels * sizeof(int16_t));
   slock_unlock(handle->lock);
   scond_signal(handle->cond);

   return true;
}