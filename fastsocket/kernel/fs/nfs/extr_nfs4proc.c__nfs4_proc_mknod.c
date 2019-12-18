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
struct TYPE_4__ {void* specdata2; void* specdata1; } ;
struct TYPE_5__ {TYPE_1__ device; } ;
struct TYPE_6__ {TYPE_2__ u; int /*<<< orphan*/  ftype; } ;
struct nfs4_createdata {TYPE_3__ arg; } ;
struct inode {int dummy; } ;
struct iattr {int ia_mode; int ia_valid; } ;
struct dentry {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ATTR_MODE ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 void* MAJOR (int /*<<< orphan*/ ) ; 
 void* MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NF4BLK ; 
 int /*<<< orphan*/  NF4CHR ; 
 int /*<<< orphan*/  NF4FIFO ; 
 int /*<<< orphan*/  NF4SOCK ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 scalar_t__ S_ISFIFO (int) ; 
 int /*<<< orphan*/  S_ISSOCK (int) ; 
 struct nfs4_createdata* nfs4_alloc_createdata (struct inode*,int /*<<< orphan*/ *,struct iattr*,int /*<<< orphan*/ ) ; 
 int nfs4_do_create (struct inode*,struct dentry*,struct nfs4_createdata*) ; 
 int /*<<< orphan*/  nfs4_free_createdata (struct nfs4_createdata*) ; 

__attribute__((used)) static int _nfs4_proc_mknod(struct inode *dir, struct dentry *dentry,
		struct iattr *sattr, dev_t rdev)
{
	struct nfs4_createdata *data;
	int mode = sattr->ia_mode;
	int status = -ENOMEM;

	BUG_ON(!(sattr->ia_valid & ATTR_MODE));
	BUG_ON(!S_ISFIFO(mode) && !S_ISBLK(mode) && !S_ISCHR(mode) && !S_ISSOCK(mode));

	data = nfs4_alloc_createdata(dir, &dentry->d_name, sattr, NF4SOCK);
	if (data == NULL)
		goto out;

	if (S_ISFIFO(mode))
		data->arg.ftype = NF4FIFO;
	else if (S_ISBLK(mode)) {
		data->arg.ftype = NF4BLK;
		data->arg.u.device.specdata1 = MAJOR(rdev);
		data->arg.u.device.specdata2 = MINOR(rdev);
	}
	else if (S_ISCHR(mode)) {
		data->arg.ftype = NF4CHR;
		data->arg.u.device.specdata1 = MAJOR(rdev);
		data->arg.u.device.specdata2 = MINOR(rdev);
	}
	
	status = nfs4_do_create(dir, dentry, data);

	nfs4_free_createdata(data);
out:
	return status;
}