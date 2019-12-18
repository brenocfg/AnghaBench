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
struct conn_context {int events; int ep_fd; int end_fd; char* buf; int data_len; int flags; int /*<<< orphan*/  handler; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_MOD ; 
 int PROXY_BACKEND_EVENT ; 
 int epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  free_context (struct conn_context*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_d (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  process_close (struct conn_context*) ; 
 int /*<<< orphan*/  process_read_backend ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void process_write_backend(struct conn_context *ctx)
{
	int ep_fd, end_fd;
	int events = ctx->events;
	char *buf;
	int data_len;
	int ret;

	ep_fd = ctx->ep_fd;
	end_fd = ctx->end_fd;
	buf = ctx->buf;
	data_len = ctx->data_len;

	print_d("Process write event[%02x] on back-end socket %d\n", events, end_fd);

	if (events & (EPOLLHUP | EPOLLERR)) {
		printf("process_write_backend() with events HUP or ERR 0x%x\n", events);
		goto free_back;
	}

	struct epoll_event evt;

	if (!(ctx->flags & PROXY_BACKEND_EVENT))
	{
		printf("Write to back-end socket while back end socket not enabled\n");
		goto free_back;
	}

	ret = write(end_fd, buf, data_len);
	if (ret < 0) {
		perror("process_write() can't write back end socket");
		goto free_back;
	}

	print_d("Write %d to back-end socket %d\n", ret, end_fd);

	ctx->handler = process_read_backend;
	ctx->flags |= PROXY_BACKEND_EVENT;

	evt.events = EPOLLIN | EPOLLHUP | EPOLLERR;
	evt.data.ptr = ctx;

	ret = epoll_ctl(ep_fd, EPOLL_CTL_MOD, end_fd, &evt);
	if (ret < 0) {
		perror("Unable to add client socket read event to epoll");
		goto free_back;
	}

	goto back;

free_back:

	process_close(ctx);
	free_context(ctx);

back:

	return;
}