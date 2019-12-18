#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fd; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
typedef  int curl_socket_t ;
struct TYPE_8__ {int /*<<< orphan*/  epfd; } ;
struct TYPE_7__ {int sockfd; int action; int /*<<< orphan*/ * easy; } ;
typedef  TYPE_2__ SockInfo ;
typedef  TYPE_3__ GlobalInfo ;
typedef  int /*<<< orphan*/  CURL ;

/* Variables and functions */
 int CURL_POLL_IN ; 
 int CURL_POLL_OUT ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 scalar_t__ epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setsock(SockInfo *f, curl_socket_t s, CURL *e, int act,
                    GlobalInfo *g)
{
  struct epoll_event ev;
  int kind = ((act & CURL_POLL_IN) ? EPOLLIN : 0) |
             ((act & CURL_POLL_OUT) ? EPOLLOUT : 0);

  if(f->sockfd) {
    if(epoll_ctl(g->epfd, EPOLL_CTL_DEL, f->sockfd, NULL))
      fprintf(stderr, "EPOLL_CTL_DEL failed for fd: %d : %s\n",
              f->sockfd, strerror(errno));
  }

  f->sockfd = s;
  f->action = act;
  f->easy = e;

  ev.events = kind;
  ev.data.fd = s;
  if(epoll_ctl(g->epfd, EPOLL_CTL_ADD, s, &ev))
    fprintf(stderr, "EPOLL_CTL_ADD failed for fd: %d : %s\n",
            s, strerror(errno));
}