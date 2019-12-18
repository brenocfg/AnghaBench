#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int /*<<< orphan*/ * s_fs_info; } ;
struct smb_sb_info {scalar_t__ conn_pid; struct smb_sb_info* ops; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONN_INVALID ; 
 int /*<<< orphan*/  SIGTERM ; 
 struct smb_sb_info* SMB_SB (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct smb_sb_info*) ; 
 int /*<<< orphan*/  kill_pid (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  put_pid (scalar_t__) ; 
 int /*<<< orphan*/  smb_close_socket (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smb_lock_server (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smb_unload_nls (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smb_unlock_server (struct smb_sb_info*) ; 
 int /*<<< orphan*/  smbiod_unregister_server (struct smb_sb_info*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static void
smb_put_super(struct super_block *sb)
{
	struct smb_sb_info *server = SMB_SB(sb);

	lock_kernel();

	smb_lock_server(server);
	server->state = CONN_INVALID;
	smbiod_unregister_server(server);

	smb_close_socket(server);

	if (server->conn_pid)
		kill_pid(server->conn_pid, SIGTERM, 1);

	kfree(server->ops);
	smb_unload_nls(server);
	sb->s_fs_info = NULL;
	smb_unlock_server(server);
	put_pid(server->conn_pid);
	kfree(server);

	unlock_kernel();
}