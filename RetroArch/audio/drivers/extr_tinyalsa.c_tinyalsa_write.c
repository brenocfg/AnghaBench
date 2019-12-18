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
struct TYPE_2__ {int /*<<< orphan*/  pcm; scalar_t__ nonblock; scalar_t__ has_float; int /*<<< orphan*/  frame_bits; } ;
typedef  TYPE_1__ tinyalsa_t ;
typedef  int ssize_t ;
typedef  int snd_pcm_sframes_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int BYTES_TO_FRAMES (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcm_wait (int /*<<< orphan*/ ,int) ; 
 int pcm_writei (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static ssize_t
tinyalsa_write(void *data, const void *buf_, size_t size_)
{
   tinyalsa_t *tinyalsa      = (tinyalsa_t*)data;
   const uint8_t *buf        = (const uint8_t*)buf_;
   snd_pcm_sframes_t written = 0;
   snd_pcm_sframes_t size    = BYTES_TO_FRAMES(size_, tinyalsa->frame_bits);
   size_t frames_size        = tinyalsa->has_float ? sizeof(float) : sizeof(int16_t);

   if (tinyalsa->nonblock)
   {
      while (size)
      {
         snd_pcm_sframes_t frames   = pcm_writei(tinyalsa->pcm, buf, size);

         if (frames < 0)
            pcm_stop(tinyalsa->pcm);

         written += frames;
         buf     += (frames << 1) * frames_size;
         size    -= frames;
      }
   }
   else
   {
      while (size)
      {
         snd_pcm_sframes_t frames;
         pcm_wait(tinyalsa->pcm, -1);

         frames   = pcm_writei(tinyalsa->pcm, buf, size);

         if (frames < 0)
            return -1;

         written += frames;
         buf     += (frames << 1) * frames_size;
         size    -= frames;
      }
   }

   return written;

}