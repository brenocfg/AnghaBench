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
struct linuxraw_joypad {int fd; int /*<<< orphan*/  ident; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ptr; } ;
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int IN_ATTRIB ; 
 int IN_CREATE ; 
 int IN_DELETE ; 
 unsigned int MAX_USERS ; 
 int O_NONBLOCK ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int epoll_create (int) ; 
 scalar_t__ epoll_ctl (int,int /*<<< orphan*/ ,scalar_t__,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  inotify_add_watch (scalar_t__,char*,int) ; 
 scalar_t__ inotify_init () ; 
 int /*<<< orphan*/  input_autoconfigure_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * input_device_names ; 
 int linuxraw_epoll ; 
 int linuxraw_hotplug ; 
 scalar_t__ linuxraw_inotify ; 
 scalar_t__ linuxraw_joypad_init_pad (char*,struct linuxraw_joypad*) ; 
 int /*<<< orphan*/ * linuxraw_pads ; 
 int /*<<< orphan*/  linuxraw_poll_pad (struct linuxraw_joypad*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool linuxraw_joypad_init(void *data)
{
   unsigned i;
   int fd = epoll_create(32);

   if (fd < 0)
      return false;

   linuxraw_epoll = fd;

   for (i = 0; i < MAX_USERS; i++)
   {
      char path[PATH_MAX_LENGTH];
      struct linuxraw_joypad *pad = (struct linuxraw_joypad*)&linuxraw_pads[i];

      path[0]                     = '\0';

      pad->fd                     = -1;
      pad->ident                  = input_device_names[i];

      snprintf(path, sizeof(path), "/dev/input/js%u", i);

      input_autoconfigure_connect(
            pad->ident,
            NULL,
            "linuxraw",
            i,
            0,
            0);

      if (linuxraw_joypad_init_pad(path, pad))
         linuxraw_poll_pad(pad);
   }

   linuxraw_inotify = inotify_init();

   if (linuxraw_inotify >= 0)
   {
      struct epoll_event event;

      fcntl(linuxraw_inotify, F_SETFL, fcntl(linuxraw_inotify, F_GETFL) | O_NONBLOCK);
      inotify_add_watch(linuxraw_inotify, "/dev/input", IN_DELETE | IN_CREATE | IN_ATTRIB);

      event.events             = EPOLLIN;
      event.data.ptr           = NULL;

      /* Shouldn't happen, but just check it. */
      if (epoll_ctl(linuxraw_epoll, EPOLL_CTL_ADD, linuxraw_inotify, &event) < 0)
      {
         RARCH_ERR("Failed to add FD (%d) to epoll list (%s).\n",
               linuxraw_inotify, strerror(errno));
      }
   }

   linuxraw_hotplug = true;

   return true;
}