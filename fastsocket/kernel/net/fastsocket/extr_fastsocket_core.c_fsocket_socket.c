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
struct socket_alloc {int dummy; } ;
struct socket {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {TYPE_1__* nsproxy; } ;
struct TYPE_3__ {int /*<<< orphan*/  net_ns; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 TYPE_2__* current ; 
 int fsock_map_fd (struct socket*,int) ; 
 int /*<<< orphan*/  fsock_release_sock (struct socket*) ; 
 struct socket* fsocket_alloc_socket () ; 
 int /*<<< orphan*/  fsocket_close (int) ; 
 int /*<<< orphan*/  fsocket_free_socket_mem (struct socket_alloc*) ; 
 int /*<<< orphan*/  fsocket_init_socket (struct socket*) ; 
 int inet_create (int /*<<< orphan*/ ,struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int security_socket_post_create (struct socket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fsocket_socket(int flags)
{
	struct socket *sock;
	int fd;

	int err = 0;

	if (flags & ~(SOCK_CLOEXEC | SOCK_NONBLOCK)) {
		EPRINTK_LIMIT(ERR, "Unsupported Socket Flags For Fastsocket\n");
		err = -EINVAL;
		goto out;
	}

	sock = fsocket_alloc_socket();
	if (sock == NULL) {
		EPRINTK_LIMIT(ERR, "Allocate New Socket failed\n");
		err = -ENOMEM;
		goto out;
	}

	sock->type = SOCK_STREAM;

	err = inet_create(current->nsproxy->net_ns, sock, 0, 0);
	if (err < 0) {
		EPRINTK_LIMIT(ERR, "Initialize Inet Socket failed\n");
		goto free_sock;
	}

	fsocket_init_socket(sock);

	fd = fsock_map_fd(sock, flags);
	if (fd < 0) {
		err = fd;
		EPRINTK_LIMIT(ERR, "Map Socket FD failed\n");
		goto release_sock;
	}

	err = security_socket_post_create(sock, PF_INET, SOCK_STREAM, IPPROTO_TCP, 0);
	if (err) {
		EPRINTK_LIMIT(ERR, "security_socket_post_create failed\n");
		fsocket_close(fd);
		return err;
	}

	return fd;

release_sock:
	fsock_release_sock(sock);
free_sock:
	fsocket_free_socket_mem((struct socket_alloc*)sock);
out:
	return err;
}