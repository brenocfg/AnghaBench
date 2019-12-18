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
struct TYPE_2__ {struct conn_context* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
struct conn_context {int ep_fd; int fd; int end_fd; scalar_t__ end_fd_added; scalar_t__ fd_added; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int /*<<< orphan*/  EPOLL_CTL_DEL ; 
 int /*<<< orphan*/  close (int) ; 
 int epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static void process_close(struct conn_context *ctx)
{
	int fd, end_fd, ep_fd, ret;
	struct epoll_event evt;

	ep_fd = ctx->ep_fd;
	fd = ctx->fd;
	end_fd = ctx->end_fd;

	evt.events = EPOLLHUP | EPOLLERR;
	evt.data.ptr = ctx;


	if (ctx->fd_added) {
		ret = epoll_ctl(ep_fd, EPOLL_CTL_DEL, fd, &evt);
		if (ret < 0)
			perror("Unable to delete client socket from epoll");
	}
	close(fd);

	if (end_fd) {
		if (ctx->end_fd_added) {
			ret = epoll_ctl(ep_fd, EPOLL_CTL_DEL, end_fd, &evt);
			if (ret < 0)
				perror("Unable to delete client socket from epoll");
		}
		close(end_fd);
	}
}