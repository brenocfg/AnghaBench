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
struct qstr {int len; char* name; } ;
struct pohmelfs_sb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;
struct pohmelfs_inode {int /*<<< orphan*/  ino; TYPE_1__ vfs_inode; } ;
struct netfs_trans {int dummy; } ;
struct netfs_cmd {int ext; int size; int /*<<< orphan*/  start; int /*<<< orphan*/  id; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  NETFS_RENAME ; 
 struct pohmelfs_sb* POHMELFS_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netfs_convert_cmd (struct netfs_cmd*) ; 
 struct netfs_trans* netfs_trans_alloc (struct pohmelfs_sb*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct netfs_cmd* netfs_trans_current (struct netfs_trans*) ; 
 int netfs_trans_finish (struct netfs_trans*,struct pohmelfs_sb*) ; 
 int /*<<< orphan*/  netfs_trans_free (struct netfs_trans*) ; 
 int /*<<< orphan*/  netfs_trans_update (struct netfs_cmd*,struct netfs_trans*,int) ; 
 int pohmelfs_construct_path_string (struct pohmelfs_inode*,char*,int) ; 
 int pohmelfs_path_length (struct pohmelfs_inode*) ; 
 int snprintf (char*,int,char*,char*) ; 

__attribute__((used)) static int pohmelfs_send_rename(struct pohmelfs_inode *pi, struct pohmelfs_inode *parent,
		struct qstr *str)
{
	int path_len, err, total_len = 0, inode_len, parent_len;
	char *path;
	struct netfs_trans *t;
	struct netfs_cmd *cmd;
	struct pohmelfs_sb *psb = POHMELFS_SB(pi->vfs_inode.i_sb);

	parent_len = pohmelfs_path_length(parent);
	inode_len = pohmelfs_path_length(pi);

	if (parent_len < 0 || inode_len < 0)
		return -EINVAL;

	path_len = parent_len + inode_len + str->len + 3;

	t = netfs_trans_alloc(psb, path_len, 0, 0);
	if (!t)
		return -ENOMEM;

	cmd = netfs_trans_current(t);
	path = (char *)(cmd + 1);

	err = pohmelfs_construct_path_string(pi, path, inode_len);
	if (err < 0)
		goto err_out_unlock;

	cmd->ext = err;

	path += err;
	total_len += err;
	path_len -= err;

	*path = '|';
	path++;
	total_len++;
	path_len--;

	err = pohmelfs_construct_path_string(parent, path, parent_len);
	if (err < 0)
		goto err_out_unlock;

	/*
	 * Do not place a null-byte before the final slash and the name.
	 */
	err--;
	path += err;
	total_len += err;
	path_len -= err;

	err = snprintf(path, path_len - 1, "/%s", str->name);

	total_len += err + 1; /* 0 symbol */
	path_len -= err + 1;

	cmd->cmd = NETFS_RENAME;
	cmd->id = pi->ino;
	cmd->start = parent->ino;
	cmd->size = total_len;

	netfs_convert_cmd(cmd);

	netfs_trans_update(cmd, t, total_len);

	return netfs_trans_finish(t, psb);

err_out_unlock:
	netfs_trans_free(t);
	return err;
}