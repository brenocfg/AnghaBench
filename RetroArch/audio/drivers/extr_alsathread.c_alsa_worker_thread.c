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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  snd_pcm_sframes_t ;
struct TYPE_2__ {int thread_dead; int /*<<< orphan*/  cond_lock; int /*<<< orphan*/  cond; int /*<<< orphan*/  pcm; int /*<<< orphan*/  period_frames; scalar_t__ period_size; int /*<<< orphan*/  fifo_lock; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_1__ alsa_thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  EPIPE ; 
 int /*<<< orphan*/  ESTRPIPE ; 
 size_t MIN (scalar_t__,size_t) ; 
 int /*<<< orphan*/  RARCH_ERR (char*,...) ; 
 scalar_t__ calloc (int,scalar_t__) ; 
 int /*<<< orphan*/  fifo_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 size_t fifo_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ snd_pcm_recover (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_writei (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alsa_worker_thread(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   uint8_t        *buf = (uint8_t *)calloc(1, alsa->period_size);

   if (!buf)
   {
      RARCH_ERR("failed to allocate audio buffer");
      goto end;
   }

   while (!alsa->thread_dead)
   {
      size_t avail;
      size_t fifo_size;
      snd_pcm_sframes_t frames;
      slock_lock(alsa->fifo_lock);
      avail = fifo_read_avail(alsa->buffer);
      fifo_size = MIN(alsa->period_size, avail);
      fifo_read(alsa->buffer, buf, fifo_size);
      scond_signal(alsa->cond);
      slock_unlock(alsa->fifo_lock);

      /* If underrun, fill rest with silence. */
      memset(buf + fifo_size, 0, alsa->period_size - fifo_size);

      frames = snd_pcm_writei(alsa->pcm, buf, alsa->period_frames);

      if (frames == -EPIPE || frames == -EINTR ||
            frames == -ESTRPIPE)
      {
         if (snd_pcm_recover(alsa->pcm, frames, 1) < 0)
         {
            RARCH_ERR("[ALSA]: (#2) Failed to recover from error (%s)\n",
                  snd_strerror(frames));
            break;
         }

         continue;
      }
      else if (frames < 0)
      {
         RARCH_ERR("[ALSA]: Unknown error occurred (%s).\n",
               snd_strerror(frames));
         break;
      }
   }

end:
   slock_lock(alsa->cond_lock);
   alsa->thread_dead = true;
   scond_signal(alsa->cond);
   slock_unlock(alsa->cond_lock);
   free(buf);
}