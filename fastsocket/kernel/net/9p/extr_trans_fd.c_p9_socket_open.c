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
struct socket {TYPE_2__* sk; } ;
struct p9_trans_fd {TYPE_1__* rd; } ;
struct p9_client {scalar_t__ trans; } ;
struct TYPE_4__ {int /*<<< orphan*/  sk_allocation; } ;
struct TYPE_3__ {int /*<<< orphan*/  f_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  P9_EPRINTK (int /*<<< orphan*/ ,char*) ; 
 int p9_fd_open (struct p9_client*,int,int) ; 
 int sock_map_fd (struct socket*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sockfd_put (struct socket*) ; 

__attribute__((used)) static int p9_socket_open(struct p9_client *client, struct socket *csocket)
{
	int fd, ret;

	csocket->sk->sk_allocation = GFP_NOIO;
	fd = sock_map_fd(csocket, 0);
	if (fd < 0) {
		P9_EPRINTK(KERN_ERR, "p9_socket_open: failed to map fd\n");
		return fd;
	}

	ret = p9_fd_open(client, fd, fd);
	if (ret < 0) {
		P9_EPRINTK(KERN_ERR, "p9_socket_open: failed to open fd\n");
		sockfd_put(csocket);
		return ret;
	}

	((struct p9_trans_fd *)client->trans)->rd->f_flags |= O_NONBLOCK;

	return 0;
}