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
struct TYPE_6__ {int fd; } ;
struct TYPE_5__ {int /*<<< orphan*/  pollFd; } ;
typedef  TYPE_1__ HttpThread ;
typedef  TYPE_2__ HttpContext ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taosCloseSocket (int) ; 

void httpRemoveContextFromEpoll(HttpThread *pThread, HttpContext *pContext) {
  if (pContext->fd >= 0) {
    epoll_ctl(pThread->pollFd, EPOLL_CTL_DEL, pContext->fd, NULL);
    taosCloseSocket(pContext->fd);
    pContext->fd = -1;
  }
}