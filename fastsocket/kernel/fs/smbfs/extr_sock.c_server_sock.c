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
struct socket {int dummy; } ;
struct smb_sb_info {struct file* sock_file; } ;
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARANOIA (char*) ; 
 struct socket* SOCKET_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smb_valid_socket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct socket *
server_sock(struct smb_sb_info *server)
{
	struct file *file;

	if (server && (file = server->sock_file))
	{
#ifdef SMBFS_PARANOIA
		if (!smb_valid_socket(file->f_path.dentry->d_inode))
			PARANOIA("bad socket!\n");
#endif
		return SOCKET_I(file->f_path.dentry->d_inode);
	}
	return NULL;
}