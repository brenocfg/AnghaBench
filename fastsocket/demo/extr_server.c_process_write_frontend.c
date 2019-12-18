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
struct conn_context {int cpu_id; int fd; char* buf; int data_len; int flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  trancnt; } ;

/* Variables and functions */
 int PROXY_BACKEND_EVENT ; 
 int /*<<< orphan*/  free_context (struct conn_context*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  print_d (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  process_close (struct conn_context*) ; 
 TYPE_1__* wdata ; 
 int write (int,char*,int) ; 

__attribute__((used)) static void process_write_frontend(struct conn_context *ctx)
{
	int front_fd;
	char *buf;
	int data_len;
	int cpu_id;
	int ret;

	cpu_id = ctx->cpu_id;
	front_fd = ctx->fd;
	buf = ctx->buf;
	data_len = ctx->data_len;

	if (ctx->flags & PROXY_BACKEND_EVENT) {
		printf("Write to front end socket while back end socket enabled\n");
		goto free_back;
	}

	ret = write(front_fd, buf, data_len);
	if (ret < 0) {
		perror("Can't write front-end socket");
		goto free_back;
	}

	print_d("Write %d to front end socket %d\n", data_len, front_fd);

	wdata[cpu_id].trancnt++;

free_back:

	process_close(ctx);
	free_context(ctx);

	return;
}