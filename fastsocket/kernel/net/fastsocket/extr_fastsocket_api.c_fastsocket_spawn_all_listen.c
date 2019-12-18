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
struct socket {TYPE_1__* sk; } ;
struct files_struct {int dummy; } ;
struct file {int f_mode; int /*<<< orphan*/  sub_file; struct socket* private_data; } ;
struct fdtable {unsigned int max_fds; int /*<<< orphan*/ * fd; int /*<<< orphan*/  open_fds; } ;
struct TYPE_4__ {int /*<<< orphan*/  pid; struct files_struct* files; } ;
struct TYPE_3__ {scalar_t__ sk_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG ; 
 int /*<<< orphan*/  DPRINTK (int /*<<< orphan*/ ,char*,unsigned int,...) ; 
 scalar_t__ FD_ISSET (unsigned int,int /*<<< orphan*/ ) ; 
 int FMODE_FASTSOCKET ; 
 scalar_t__ TCP_LISTEN ; 
 TYPE_2__* current ; 
 struct fdtable* files_fdtable (struct files_struct*) ; 
 int /*<<< orphan*/  fscoket_spawn_restore (struct socket*,unsigned int) ; 
 scalar_t__ fsocket_spawn (struct file*,unsigned int,int) ; 
 struct file* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int fastsocket_spawn_all_listen(void)
{
	struct files_struct *files = current->files;
	struct fdtable *fdt;
	struct file *file;
	unsigned int i;
	int ret = 0;

	DPRINTK(DEBUG, "Spawn all listen socket of pid(%u)\n", current->pid);

	rcu_read_lock();
	fdt = files_fdtable(files);

	for (i = 0; i < fdt->max_fds; ++i) {
		if (FD_ISSET(i, fdt->open_fds)) {
			file = rcu_dereference(fdt->fd[i]);
			if (file && file->f_mode & FMODE_FASTSOCKET) {
				struct socket * sock = file->private_data;

				DPRINTK(DEBUG, "fd(%d) is fastsocket fd, sock state(%d) subfile(%p)\n", 
					i, sock->sk->sk_state, file->sub_file);

				if (sock->sk->sk_state == TCP_LISTEN) {
					if (file->sub_file) {
						// The parent process has already spawn, we need to free the old one.
						fscoket_spawn_restore(sock, i);
						// Need to get the file again;
						file = rcu_dereference(fdt->fd[i]);
					}
					ret += fsocket_spawn(file, i, -1);
				}
			}

			rcu_read_unlock();
		}
	}
	rcu_read_unlock();

	return ret;
}