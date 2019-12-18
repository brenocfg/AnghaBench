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
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
struct pcm {TYPE_1__* mmap_status; TYPE_2__* sync_ptr; int /*<<< orphan*/  fd; } ;
struct TYPE_4__ {scalar_t__ flags; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int EINTR ; 
 int EIO ; 
 int ENODEV ; 
 int EPIPE ; 
 int ESTRPIPE ; 
#define  PCM_STATE_DISCONNECTED 130 
#define  PCM_STATE_SUSPENDED 129 
#define  PCM_STATE_XRUN 128 
 int POLLERR ; 
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLOUT ; 
 int /*<<< orphan*/  SNDRV_PCM_IOCTL_SYNC_PTR ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int poll (struct pollfd*,int,int) ; 

__attribute__((used)) static int pcm_wait(struct pcm *pcm, int timeout)
{
   struct pollfd pfd;

   pfd.fd     = pcm->fd;
   pfd.events = POLLIN | POLLOUT | POLLERR | POLLNVAL;

   do
   {
      /* let's wait for avail or timeout */
      int err = poll(&pfd, 1, timeout);
      if (err < 0)
         return -errno;

      /* timeout ? */
      if (err == 0)
         return 0;

      /* have we been interrupted ? */
      if (errno == -EINTR)
         continue;

      /* check for any errors */
      if (pfd.revents & (POLLERR | POLLNVAL))
      {
         int cond = -1;

         if (pcm->sync_ptr)
         {
            pcm->sync_ptr->flags = 0;
            if (ioctl(pcm->fd, SNDRV_PCM_IOCTL_SYNC_PTR, pcm->sync_ptr) >= 0)
               cond = pcm->mmap_status->state;
         }

         switch (cond)
         {
            case PCM_STATE_XRUN:
               return -EPIPE;
            case PCM_STATE_SUSPENDED:
               return -ESTRPIPE;
            case PCM_STATE_DISCONNECTED:
               return -ENODEV;
            default:
               break;
         }

         return -EIO;
      }
      /* poll again if fd not ready for IO */
   } while (!(pfd.revents & (POLLIN | POLLOUT)));

   return 1;
}