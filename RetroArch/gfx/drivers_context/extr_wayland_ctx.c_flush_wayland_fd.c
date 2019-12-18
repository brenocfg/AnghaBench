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
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  dpy; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ input_ctx_wayland_data_t ;

/* Variables and functions */
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  frontend_driver_set_signal_handler_state (int) ; 
 scalar_t__ poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_dispatch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_dispatch_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_flush (int /*<<< orphan*/ ) ; 

void flush_wayland_fd(void *data)
{
   struct pollfd fd = {0};
   input_ctx_wayland_data_t *wl = (input_ctx_wayland_data_t*)data;

   wl_display_dispatch_pending(wl->dpy);
   wl_display_flush(wl->dpy);

   fd.fd     = wl->fd;
   fd.events = POLLIN | POLLOUT | POLLERR | POLLHUP;

   if (poll(&fd, 1, 0) > 0)
   {
      if (fd.revents & (POLLERR | POLLHUP))
      {
         close(wl->fd);
         frontend_driver_set_signal_handler_state(1);
      }

      if (fd.revents & POLLIN)
         wl_display_dispatch(wl->dpy);
      if (fd.revents & POLLOUT)
         wl_display_flush(wl->dpy);
   }
}