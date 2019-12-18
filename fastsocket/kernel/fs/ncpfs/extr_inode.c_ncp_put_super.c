#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct TYPE_6__ {struct ncp_server* object_name; } ;
struct TYPE_5__ {struct ncp_server* data; } ;
struct TYPE_4__ {int /*<<< orphan*/  wdog_pid; } ;
struct ncp_server {int /*<<< orphan*/  packet; int /*<<< orphan*/  txbuf; int /*<<< orphan*/  rxbuf; TYPE_3__ auth; TYPE_2__ priv; TYPE_1__ m; scalar_t__ ncp_filp; scalar_t__ info_filp; int /*<<< orphan*/  nls_io; int /*<<< orphan*/  nls_vol; } ;

/* Variables and functions */
 struct ncp_server* NCP_SBP (struct super_block*) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  fput (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ncp_server*) ; 
 int /*<<< orphan*/  kill_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  ncp_disconnect (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_lock_server (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_stop_tasks (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_unlock_server (struct ncp_server*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unload_nls (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ncp_put_super(struct super_block *sb)
{
	struct ncp_server *server = NCP_SBP(sb);

	lock_kernel();

	ncp_lock_server(server);
	ncp_disconnect(server);
	ncp_unlock_server(server);

	ncp_stop_tasks(server);

#ifdef CONFIG_NCPFS_NLS
	/* unload the NLS charsets */
	unload_nls(server->nls_vol);
	unload_nls(server->nls_io);
#endif /* CONFIG_NCPFS_NLS */

	if (server->info_filp)
		fput(server->info_filp);
	fput(server->ncp_filp);
	kill_pid(server->m.wdog_pid, SIGTERM, 1);
	put_pid(server->m.wdog_pid);

	kfree(server->priv.data);
	kfree(server->auth.object_name);
	vfree(server->rxbuf);
	vfree(server->txbuf);
	vfree(server->packet);
	sb->s_fs_info = NULL;
	kfree(server);

	unlock_kernel();
}