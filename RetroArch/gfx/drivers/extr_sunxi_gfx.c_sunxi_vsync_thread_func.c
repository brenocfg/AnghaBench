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
struct sunxi_video {int pageflip_pending; int /*<<< orphan*/  pending_mutex; int /*<<< orphan*/  vsync_condition; int /*<<< orphan*/ * pages; int /*<<< orphan*/ * nextPage; TYPE_1__* sunxi_disp; scalar_t__ keep_vsync; } ;
struct TYPE_2__ {int /*<<< orphan*/  fd_fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  FBIO_WAITFORVSYNC ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scond_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slock_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sunxi_vsync_thread_func(void *data)
{
   struct sunxi_video *_dispvars = (struct sunxi_video*)data;

   while (_dispvars->keep_vsync)
   {
      /* Wait for next vsync */
      ioctl(_dispvars->sunxi_disp->fd_fb, FBIO_WAITFORVSYNC, 0);

      /* Changing the page to write must be done before the signaling
       * so we have the right page in nextPage when update_main continues */
      if (_dispvars->nextPage == &_dispvars->pages[0])
         _dispvars->nextPage = &_dispvars->pages[1];
      else
         _dispvars->nextPage = &_dispvars->pages[0];

      /* These two things must be isolated "atomically" to avoid getting
       * a false positive in the pending_mutex test in update_main. */
      slock_lock(_dispvars->pending_mutex);
      _dispvars->pageflip_pending = false;
      scond_signal(_dispvars->vsync_condition);
      slock_unlock(_dispvars->pending_mutex);
   }
}