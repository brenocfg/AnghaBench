#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ncp_server {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  volNumber; } ;
struct ncp_entry_info {TYPE_4__ i; int /*<<< orphan*/  volume; int /*<<< orphan*/  ino; scalar_t__ opened; } ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_3__* d_parent; TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __name ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_2__ d_name; } ;

/* Variables and functions */
 int EACCES ; 
 int EIO ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  NCP_MAXPATHLEN ; 
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  PPRINTK (char*,int,...) ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  iunique (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  ncp_conn_valid (struct ncp_server*) ; 
 int /*<<< orphan*/  ncp_dentry_operations ; 
 struct inode* ncp_iget (int /*<<< orphan*/ ,struct ncp_entry_info*) ; 
 int ncp_io2vol (struct ncp_server*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ncp_is_server_root (struct inode*) ; 
 int ncp_lookup_volume (struct ncp_server*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ncp_new_dentry (struct dentry*) ; 
 int ncp_obtain_info (struct ncp_server*,struct inode*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ncp_preserve_case (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static struct dentry *ncp_lookup(struct inode *dir, struct dentry *dentry, struct nameidata *nd)
{
	struct ncp_server *server = NCP_SERVER(dir);
	struct inode *inode = NULL;
	struct ncp_entry_info finfo;
	int error, res, len;
	__u8 __name[NCP_MAXPATHLEN + 1];

	lock_kernel();
	error = -EIO;
	if (!ncp_conn_valid(server))
		goto finished;

	PPRINTK("ncp_lookup: server lookup for %s/%s\n",
		dentry->d_parent->d_name.name, dentry->d_name.name);

	len = sizeof(__name);
	if (ncp_is_server_root(dir)) {
		res = ncp_io2vol(server, __name, &len, dentry->d_name.name,
				 dentry->d_name.len, 1);
		if (!res)
			res = ncp_lookup_volume(server, __name, &(finfo.i));
	} else {
		res = ncp_io2vol(server, __name, &len, dentry->d_name.name,
				 dentry->d_name.len, !ncp_preserve_case(dir));
		if (!res)
			res = ncp_obtain_info(server, dir, __name, &(finfo.i));
	}
	PPRINTK("ncp_lookup: looked for %s/%s, res=%d\n",
		dentry->d_parent->d_name.name, __name, res);
	/*
	 * If we didn't find an entry, make a negative dentry.
	 */
	if (res)
		goto add_entry;

	/*
	 * Create an inode for the entry.
	 */
	finfo.opened = 0;
	finfo.ino = iunique(dir->i_sb, 2);
	finfo.volume = finfo.i.volNumber;
	error = -EACCES;
	inode = ncp_iget(dir->i_sb, &finfo);

	if (inode) {
		ncp_new_dentry(dentry);
add_entry:
		dentry->d_op = &ncp_dentry_operations;
		d_add(dentry, inode);
		error = 0;
	}

finished:
	PPRINTK("ncp_lookup: result=%d\n", error);
	unlock_kernel();
	return ERR_PTR(error);
}