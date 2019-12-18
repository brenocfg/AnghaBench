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
struct ncp_server {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; TYPE_2__* d_parent; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __name ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EACCES ; 
 int EBUSY ; 
 int EIO ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int EPERM ; 
 int /*<<< orphan*/  NCP_MAXPATHLEN ; 
 struct ncp_server* NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  ncp_conn_valid (struct ncp_server*) ; 
 int ncp_del_file_or_subdir (struct ncp_server*,struct inode*,int /*<<< orphan*/ *) ; 
 int ncp_io2vol (struct ncp_server*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncp_preserve_case (struct inode*) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int ncp_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct ncp_server *server = NCP_SERVER(dir);
	int error, result, len;
	__u8 __name[NCP_MAXPATHLEN + 1];

	DPRINTK("ncp_rmdir: removing %s/%s\n",
		dentry->d_parent->d_name.name, dentry->d_name.name);

	error = -EIO;
	lock_kernel();
	if (!ncp_conn_valid(server))
		goto out;

	error = -EBUSY;
	if (!d_unhashed(dentry))
		goto out;

	len = sizeof(__name);
	error = ncp_io2vol(server, __name, &len, dentry->d_name.name,
			   dentry->d_name.len, !ncp_preserve_case(dir));
	if (error)
		goto out;

	result = ncp_del_file_or_subdir(server, dir, __name);
	switch (result) {
		case 0x00:
			error = 0;
			break;
		case 0x85:	/* unauthorized to delete file */
		case 0x8A:	/* unauthorized to delete file */
			error = -EACCES;
			break;
		case 0x8F:
		case 0x90:	/* read only */
			error = -EPERM;
			break;
		case 0x9F:	/* in use by another client */
			error = -EBUSY;
			break;
		case 0xA0:	/* directory not empty */
			error = -ENOTEMPTY;
			break;
		case 0xFF:	/* someone deleted file */
			error = -ENOENT;
			break;
		default:
			error = -EACCES;
			break;
       	}
out:
	unlock_kernel();
	return error;
}