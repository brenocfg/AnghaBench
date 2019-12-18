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
struct nfs_client {struct idmap* cl_idmap; TYPE_2__* cl_rpcclient; } ;
struct TYPE_8__ {int /*<<< orphan*/  h_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  h_type; } ;
struct idmap {TYPE_4__ idmap_group_hash; TYPE_3__ idmap_user_hash; int /*<<< orphan*/  idmap_wq; int /*<<< orphan*/  idmap_im_lock; int /*<<< orphan*/  idmap_lock; int /*<<< orphan*/  idmap_dentry; } ;
struct TYPE_5__ {int /*<<< orphan*/  dentry; } ;
struct TYPE_6__ {TYPE_1__ cl_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IDMAP_TYPE_GROUP ; 
 int /*<<< orphan*/  IDMAP_TYPE_USER ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idmap_upcall_ops ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct idmap*) ; 
 struct idmap* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rpc_mkpipe (int /*<<< orphan*/ ,char*,struct idmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nfs_idmap_new(struct nfs_client *clp)
{
	struct idmap *idmap;
	int error;

	BUG_ON(clp->cl_idmap != NULL);

	idmap = kzalloc(sizeof(*idmap), GFP_KERNEL);
	if (idmap == NULL)
		return -ENOMEM;

	idmap->idmap_dentry = rpc_mkpipe(clp->cl_rpcclient->cl_path.dentry,
			"idmap", idmap, &idmap_upcall_ops, 0);
	if (IS_ERR(idmap->idmap_dentry)) {
		error = PTR_ERR(idmap->idmap_dentry);
		kfree(idmap);
		return error;
	}

	mutex_init(&idmap->idmap_lock);
	mutex_init(&idmap->idmap_im_lock);
	init_waitqueue_head(&idmap->idmap_wq);
	idmap->idmap_user_hash.h_type = IDMAP_TYPE_USER;
	idmap->idmap_group_hash.h_type = IDMAP_TYPE_GROUP;

	clp->cl_idmap = idmap;
	return 0;
}