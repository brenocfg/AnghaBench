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
struct TYPE_3__ {struct conn_context* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
struct conn_context {int events; char* buf; int cpu_id; int ep_fd; int fd; int data_len; int /*<<< orphan*/  handler; } ;
struct TYPE_4__ {int /*<<< orphan*/  read_cnt; } ;

/* Variables and functions */
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLOUT ; 
 int /*<<< orphan*/  EPOLL_CTL_MOD ; 
 int /*<<< orphan*/  MAX_BUFSIZE ; 
 int epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  free_context (struct conn_context*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_d (char*,...) ; 
 int /*<<< orphan*/  process_close (struct conn_context*) ; 
 int /*<<< orphan*/  process_write ; 
 int read (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* wdata ; 

__attribute__((used)) static void process_read(struct conn_context *client_ctx)
{
	int ep_fd, fd;
	int events = client_ctx->events;
	struct epoll_event evt;
	int ret;
	char *buf = client_ctx->buf;
	int cpu_id = client_ctx->cpu_id;

	ep_fd = client_ctx->ep_fd;
	fd = client_ctx->fd;

	//FIXME: What else should I do.
	if (events & EPOLLHUP) {
		print_d("process_read() with events HUP\n");
		goto free_back;
	}
	if (events & EPOLLERR) {
		print_d("process_read() with events ERR\n");
		goto free_back;
	}

	print_d("Process read event[%02x] on socket %d\n", events, fd);

	ret = read(fd, buf, MAX_BUFSIZE);
	if (ret < 0) {
		wdata[cpu_id].read_cnt++;
		perror("process_read() can't read client socket");
		goto free_back;
	} else if (ret == 0) {
		goto free_back;
		print_d("Socket %d is closed\n", fd);
	}

	client_ctx->data_len = ret;

	print_d("Read %d from socket %d\n", ret, fd);

	client_ctx->handler = process_write;

	evt.events = EPOLLOUT | EPOLLHUP | EPOLLERR;
	evt.data.ptr = client_ctx;

	ret = epoll_ctl(ep_fd, EPOLL_CTL_MOD, fd, &evt);
	if (ret < 0) {
		perror("Unable to add client socket read event to epoll");
		goto free_back;
	}

	goto back;


free_back:

	print_d("cpu[%d] close socket %d\n", cpu_id, client_ctx->fd);

	process_close(client_ctx);
	free_context(client_ctx);

back:
	return;
}