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
struct page {int dummy; } ;
struct TYPE_7__ {int fromname; unsigned int pathlen; struct iattr* sattr; struct page** pages; int /*<<< orphan*/  fromlen; int /*<<< orphan*/  fromfh; } ;
struct TYPE_8__ {TYPE_3__ symlink; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rpc_proc; } ;
struct nfs3_createdata {TYPE_4__ arg; TYPE_1__ msg; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct TYPE_6__ {int name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; } ;

/* Variables and functions */
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 size_t NFS3PROC_SYMLINK ; 
 unsigned int NFS3_MAXPATHLEN ; 
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 struct nfs3_createdata* nfs3_alloc_createdata () ; 
 int nfs3_do_create (struct inode*,struct dentry*,struct nfs3_createdata*) ; 
 int /*<<< orphan*/  nfs3_free_createdata (struct nfs3_createdata*) ; 
 int /*<<< orphan*/ * nfs3_procedures ; 

__attribute__((used)) static int
nfs3_proc_symlink(struct inode *dir, struct dentry *dentry, struct page *page,
		  unsigned int len, struct iattr *sattr)
{
	struct nfs3_createdata *data;
	int status = -ENOMEM;

	if (len > NFS3_MAXPATHLEN)
		return -ENAMETOOLONG;

	dprintk("NFS call  symlink %s\n", dentry->d_name.name);

	data = nfs3_alloc_createdata();
	if (data == NULL)
		goto out;
	data->msg.rpc_proc = &nfs3_procedures[NFS3PROC_SYMLINK];
	data->arg.symlink.fromfh = NFS_FH(dir);
	data->arg.symlink.fromname = dentry->d_name.name;
	data->arg.symlink.fromlen = dentry->d_name.len;
	data->arg.symlink.pages = &page;
	data->arg.symlink.pathlen = len;
	data->arg.symlink.sattr = sattr;

	status = nfs3_do_create(dir, dentry, data);

	nfs3_free_createdata(data);
out:
	dprintk("NFS reply symlink: %d\n", status);
	return status;
}