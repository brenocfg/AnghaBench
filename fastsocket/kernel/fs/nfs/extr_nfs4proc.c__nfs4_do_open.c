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
struct rpc_cred {int dummy; } ;
struct nfs_server {int dummy; } ;
struct nfs4_state_owner {int dummy; } ;
struct nfs4_state {int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  f_attr; } ;
struct TYPE_3__ {int open_flags; scalar_t__ createmode; } ;
struct nfs4_opendata {TYPE_2__ o_res; TYPE_1__ o_arg; int /*<<< orphan*/  state; } ;
struct inode {int dummy; } ;
struct iattr {int dummy; } ;
struct dentry {int /*<<< orphan*/ * d_inode; } ;
typedef  int /*<<< orphan*/  fmode_t ;
typedef  enum open_claim_type4 { ____Placeholder_open_claim_type4 } open_claim_type4 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NFS4_CREATE_GUARDED ; 
 int NFS4_OPEN_CLAIM_FH ; 
 int NFS4_OPEN_CLAIM_NULL ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 int O_EXCL ; 
 int _nfs4_open_and_get_state (struct nfs4_opendata*,int /*<<< orphan*/ ,int,struct nfs4_state**) ; 
 int /*<<< orphan*/  dprintk (char*) ; 
 int nfs4_do_setattr (int /*<<< orphan*/ ,struct rpc_cred*,int /*<<< orphan*/ ,struct iattr*,struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs4_exclusive_attrset (struct nfs4_opendata*,struct iattr*) ; 
 int /*<<< orphan*/  nfs4_get_open_state (int /*<<< orphan*/ *,struct nfs4_state_owner*) ; 
 struct nfs4_state_owner* nfs4_get_state_owner (struct nfs_server*,struct rpc_cred*) ; 
 struct nfs4_opendata* nfs4_opendata_alloc (struct dentry*,struct nfs4_state_owner*,int /*<<< orphan*/ ,int,struct iattr*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_opendata_put (struct nfs4_opendata*) ; 
 int /*<<< orphan*/  nfs4_put_state_owner (struct nfs4_state_owner*) ; 
 int nfs4_recover_expired_lease (struct nfs_server*) ; 
 int /*<<< orphan*/  nfs4_return_incompatible_delegation (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_fattr_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_post_op_update_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_setattr_update_inode (int /*<<< orphan*/ ,struct iattr*) ; 

__attribute__((used)) static int _nfs4_do_open(struct inode *dir, struct dentry *dentry, fmode_t fmode, int flags, struct iattr *sattr, struct rpc_cred *cred, struct nfs4_state **res)
{
	struct nfs4_state_owner  *sp;
	struct nfs4_state     *state = NULL;
	struct nfs_server       *server = NFS_SERVER(dir);
	struct nfs4_opendata *opendata;
	enum open_claim_type4 claim = NFS4_OPEN_CLAIM_NULL;
	int status;

	/* Protect against reboot recovery conflicts */
	status = -ENOMEM;
	if (!(sp = nfs4_get_state_owner(server, cred))) {
		dprintk("nfs4_do_open: nfs4_get_state_owner failed!\n");
		goto out_err;
	}
	status = nfs4_recover_expired_lease(server);
	if (status != 0)
		goto err_put_state_owner;
	if (dentry->d_inode != NULL)
		nfs4_return_incompatible_delegation(dentry->d_inode, fmode);
	status = -ENOMEM;
	if (dentry->d_inode)
		claim = NFS4_OPEN_CLAIM_FH;
	opendata = nfs4_opendata_alloc(dentry, sp, fmode, flags, sattr,
			claim, GFP_KERNEL);
	if (opendata == NULL)
		goto err_put_state_owner;

	if (dentry->d_inode != NULL)
		opendata->state = nfs4_get_open_state(dentry->d_inode, sp);

	status = _nfs4_open_and_get_state(opendata, fmode, flags, &state);
	if (status != 0)
		goto err_opendata_put;

	if ((opendata->o_arg.open_flags & O_EXCL) &&
	    (opendata->o_arg.createmode != NFS4_CREATE_GUARDED)) {
		nfs4_exclusive_attrset(opendata, sattr);

		nfs_fattr_init(opendata->o_res.f_attr);
		status = nfs4_do_setattr(state->inode, cred,
				opendata->o_res.f_attr, sattr,
				state);
		if (status == 0)
			nfs_setattr_update_inode(state->inode, sattr);
		nfs_post_op_update_inode(state->inode, opendata->o_res.f_attr);
	}
	nfs4_opendata_put(opendata);
	nfs4_put_state_owner(sp);
	*res = state;
	return 0;
err_opendata_put:
	nfs4_opendata_put(opendata);
err_put_state_owner:
	nfs4_put_state_owner(sp);
out_err:
	*res = NULL;
	return status;
}