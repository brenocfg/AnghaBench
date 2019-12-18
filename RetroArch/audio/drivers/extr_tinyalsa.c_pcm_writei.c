#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_xferi {unsigned int frames; int result; void* buf; } ;
struct pcm {int flags; int running; int /*<<< orphan*/  underruns; scalar_t__ prepared; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPIPE ; 
 unsigned int INT_MAX ; 
 int PCM_IN ; 
 int PCM_NORESTART ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_WRITEI_FRAMES ; 
 unsigned int TINYALSA_FRAMES_MAX ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_xferi*) ; 
 int pcm_prepare (struct pcm*) ; 

__attribute__((used)) static int pcm_writei(struct pcm *pcm, const void *data, unsigned int frame_count)
{
   struct snd_xferi x;

   if (pcm->flags & PCM_IN)
      return -EINVAL;
#if UINT_MAX > TINYALSA_FRAMES_MAX
   if (frame_count > TINYALSA_FRAMES_MAX)
      return -EINVAL;
#endif
   if (frame_count > INT_MAX)
      return -EINVAL;

   x.buf    = (void*)data;
   x.frames = frame_count;
   x.result = 0;

restart:
   if (!pcm->running)
   {
      int prepare_error = pcm_prepare(pcm);
      if (prepare_error)
         return prepare_error;
      if (ioctl(pcm->fd, SNDRV_PCM_IOCTL_WRITEI_FRAMES, &x))
      {
         RARCH_ERR("[TINYALSA]: Cannot write initial data.\n");
         return -1;
      }
      pcm->running = 1;
      return 0;
   }

   if (ioctl(pcm->fd, SNDRV_PCM_IOCTL_WRITEI_FRAMES, &x))
   {
      pcm->prepared = 0;
      pcm->running = 0;
      if (errno == EPIPE)
      {
         /* we failed to make our window -- try to restart if we are
          * allowed to do so.  Otherwise, simply allow the EPIPE error to
          * propagate up to the app level */
         pcm->underruns++;
         if (pcm->flags & PCM_NORESTART)
            return -EPIPE;
         goto restart;
      }
#if 0
      /* This tends to spam a lot */
      RARCH_ERR("[TINYALSA]: Cannot write stream data.\n");
#endif
      return -1;
   }

   return x.result;
}