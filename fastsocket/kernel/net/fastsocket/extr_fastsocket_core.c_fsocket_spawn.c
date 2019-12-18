#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct socket {TYPE_2__* ops; TYPE_4__* sk; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct file {scalar_t__ private_data; int /*<<< orphan*/  sub_file; } ;
typedef  int /*<<< orphan*/  kernel_cap_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_8__ {scalar_t__ sk_state; int sk_max_ack_backlog; } ;
struct TYPE_7__ {int /*<<< orphan*/  saddr; int /*<<< orphan*/  sport; } ;
struct TYPE_6__ {int (* bind ) (struct socket*,struct sockaddr*,int) ;int (* listen ) (struct socket*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,int,...) ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPRINTK_LIMIT (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ERR ; 
 int /*<<< orphan*/  INFO ; 
 scalar_t__ TCP_LISTEN ; 
 int /*<<< orphan*/  fastsocket_spawn_mutex ; 
 int /*<<< orphan*/  fsocket_filp_close_spawn (int) ; 
 int fsocket_process_affinity_check (int) ; 
 int /*<<< orphan*/  fsocket_process_affinity_restore (int) ; 
 int /*<<< orphan*/  fsocket_process_affinity_set (int) ; 
 int /*<<< orphan*/  fsocket_reset_bind_cap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsocket_set_bind_cap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsocket_sk_affinity_release (struct socket*) ; 
 int /*<<< orphan*/  fsocket_sk_affinity_set (struct socket*,int) ; 
 int fsocket_spawn_clone (int,struct socket*,struct socket**) ; 
 TYPE_3__* inet_sk (TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct socket*,struct sockaddr*,int) ; 
 int stub2 (struct socket*,int) ; 

int fsocket_spawn(struct file *filp, int fd, int tcpu)
{
	int ret = 0, backlog;
	int cpu;
	struct socket *sock, *newsock;
	struct sockaddr_in addr;
	kernel_cap_t p;

	DPRINTK(INFO, "Listen spawn listen fd %d on CPU %d. filp->sub_file(%p)\n", fd, tcpu, filp->sub_file);

	mutex_lock(&fastsocket_spawn_mutex);

	if (filp->sub_file) {
		EPRINTK_LIMIT(ERR, "Spawn on a already spawned file 0x%p\n", filp);
		ret = -EEXIST;
		goto out;
	}

	sock  = (struct socket *)filp->private_data;

	if (sock->sk->sk_state != TCP_LISTEN) {
		EPRINTK_LIMIT(ERR, "Spawn on a non-listen socket[%d-%d] file 0x%p\n", fd, sock->sk->sk_state, filp);
		ret = -EINVAL;
		goto out;
	}

	ret = fsocket_process_affinity_check(tcpu);
	if (ret < 0) {
		EPRINTK_LIMIT(ERR, "Set CPU affinity for process failed\n");
		goto out;
	}

	cpu = ret;
	newsock = NULL;
	ret = fsocket_spawn_clone(fd, sock, &newsock);
	if (ret < 0) {
		EPRINTK_LIMIT(ERR, "Clone listen socket failed[%d]\n", ret);
		goto restore;
	}

	fsocket_sk_affinity_set(newsock, cpu);

	fsocket_set_bind_cap(&p);

	addr.sin_family = AF_INET;
	addr.sin_port = inet_sk(sock->sk)->sport;
	addr.sin_addr.s_addr = inet_sk(sock->sk)->saddr;

	ret = newsock->ops->bind(newsock, (struct sockaddr *)&addr, sizeof(addr));
	if (ret < 0)
	{
		EPRINTK_LIMIT(ERR, "Bind spawned socket %d failed[%d]\n", fd, ret);
		goto release;
	}

	fsocket_reset_bind_cap(&p);

	backlog = sock->sk->sk_max_ack_backlog;

	ret = newsock->ops->listen(newsock, backlog);
	if (ret < 0)
	{
		EPRINTK_LIMIT(ERR, "Listen spawned socket %d failed[%d]\n", fd, ret);
		goto release;
	}

	fsocket_process_affinity_set(cpu);

	goto out;

release:
	fsocket_sk_affinity_release(newsock);
	fsocket_filp_close_spawn(fd);
restore:
	fsocket_process_affinity_restore(cpu);
out:
	mutex_unlock(&fastsocket_spawn_mutex);

	DPRINTK(DEBUG, "fsocket_spawn return value is %d\n", ret);	

	return ret;
}