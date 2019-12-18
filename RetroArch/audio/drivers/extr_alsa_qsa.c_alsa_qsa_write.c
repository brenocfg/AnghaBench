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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ssize_t ;
typedef  size_t snd_pcm_sframes_t ;
struct TYPE_3__ {scalar_t__ buf_size; scalar_t__ buffer_ptr; scalar_t__* buffer; size_t buffer_index; int buf_count; int /*<<< orphan*/  pcm; } ;
typedef  TYPE_1__ alsa_qsa_t ;

/* Variables and functions */
 size_t EAGAIN ; 
 int EBADF ; 
 int EPROTO ; 
 size_t MIN (scalar_t__,size_t) ; 
 int /*<<< orphan*/  SND_PCM_CHANNEL_PLAYBACK ; 
 int check_pcm_status (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 size_t snd_pcm_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static ssize_t alsa_qsa_write(void *data, const void *buf, size_t size)
{
   alsa_qsa_t          *alsa = (alsa_qsa_t*)data;
   snd_pcm_sframes_t written = 0;

   while (size)
   {
      size_t avail_write = MIN(alsa->buf_size - alsa->buffer_ptr, size);

      if (avail_write)
      {
         memcpy(alsa->buffer[alsa->buffer_index] +
               alsa->buffer_ptr, buf, avail_write);

         alsa->buffer_ptr      += avail_write;
         buf                    = (void*)((uint8_t*)buf + avail_write);
         size                  -= avail_write;
         written               += avail_write;
      }

      if (alsa->buffer_ptr >= alsa->buf_size)
      {
         snd_pcm_sframes_t frames = snd_pcm_write(alsa->pcm,
               alsa->buffer[alsa->buffer_index], alsa->buf_size);

         alsa->buffer_index = (alsa->buffer_index + 1) % alsa->buf_count;
         alsa->buffer_ptr   = 0;

         if (frames <= 0)
         {
            int ret;

            if (frames == -EAGAIN)
               continue;

            ret = check_pcm_status(alsa, SND_PCM_CHANNEL_PLAYBACK);

            if (ret == -EPROTO || ret == -EBADF)
               return -1;
         }
      }

   }

   return written;
}