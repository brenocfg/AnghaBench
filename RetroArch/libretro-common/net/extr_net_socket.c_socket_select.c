#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_5__ {int fd; } ;
struct TYPE_6__ {int events; TYPE_1__ data; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SceNetEpollEvent ;

/* Variables and functions */
 int SCE_NET_EPOLLHUP ; 
 int SCE_NET_EPOLLIN ; 
 int /*<<< orphan*/  SCE_NET_EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  SCE_NET_EPOLL_CTL_DEL ; 
 scalar_t__ sceNetEpollControl (int,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int sceNetEpollWait (int,TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int socketselect (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int socket_select(int nfds, fd_set *readfs, fd_set *writefds,
      fd_set *errorfds, struct timeval *timeout)
{
#if defined(__CELLOS_LV2__)
   return socketselect(nfds, readfs, writefds, errorfds, timeout);
#elif defined(VITA)
   extern int retro_epoll_fd;
   SceNetEpollEvent ev = {0};

   ev.events = SCE_NET_EPOLLIN | SCE_NET_EPOLLHUP;
   ev.data.fd = nfds;

   if((sceNetEpollControl(retro_epoll_fd, SCE_NET_EPOLL_CTL_ADD, nfds, &ev)))
   {
      int ret = sceNetEpollWait(retro_epoll_fd, &ev, 1, 0);
      sceNetEpollControl(retro_epoll_fd, SCE_NET_EPOLL_CTL_DEL, nfds, NULL);
      return ret;
   }
   return 0;
#else
   return select(nfds, readfs, writefds, errorfds, timeout);
#endif
}