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
struct nfs_inode {int /*<<< orphan*/  delegation; } ;
struct nfs_delegation {int /*<<< orphan*/  stateid; } ;
struct nfs4_state {int /*<<< orphan*/  count; TYPE_2__* owner; int /*<<< orphan*/  inode; } ;
struct TYPE_3__ {int open_flags; int /*<<< orphan*/  seqid; int /*<<< orphan*/  fmode; } ;
struct nfs4_opendata {int /*<<< orphan*/  is_recover; TYPE_1__ o_arg; struct nfs4_state* state; } ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  fmode_t ;
struct TYPE_4__ {int /*<<< orphan*/  so_cred; int /*<<< orphan*/  so_lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 struct nfs4_state* ERR_PTR (int) ; 
 struct nfs_inode* NFS_I (int /*<<< orphan*/ ) ; 
 int O_EXCL ; 
 int O_TRUNC ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ can_open_cached (struct nfs4_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  can_open_delegated (struct nfs_delegation*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int nfs_may_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfs_release_seqid (int /*<<< orphan*/ ) ; 
 struct nfs_delegation* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_open_stateflags (struct nfs4_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ update_open_stateid (struct nfs4_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nfs4_state *nfs4_try_open_cached(struct nfs4_opendata *opendata)
{
	struct nfs4_state *state = opendata->state;
	struct nfs_inode *nfsi = NFS_I(state->inode);
	struct nfs_delegation *delegation;
	int open_mode = opendata->o_arg.open_flags & (O_EXCL|O_TRUNC);
	fmode_t fmode = opendata->o_arg.fmode;
	nfs4_stateid stateid;
	int ret = -EAGAIN;

	for (;;) {
		if (can_open_cached(state, fmode, open_mode)) {
			spin_lock(&state->owner->so_lock);
			if (can_open_cached(state, fmode, open_mode)) {
				update_open_stateflags(state, fmode);
				spin_unlock(&state->owner->so_lock);
				goto out_return_state;
			}
			spin_unlock(&state->owner->so_lock);
		}
		rcu_read_lock();
		delegation = rcu_dereference(nfsi->delegation);
		if (!can_open_delegated(delegation, fmode)) {
			rcu_read_unlock();
			break;
		}
		/* Save the delegation */
		nfs4_stateid_copy(&stateid, &delegation->stateid);
		rcu_read_unlock();
		nfs_release_seqid(opendata->o_arg.seqid);
		if (!opendata->is_recover) {
			ret = nfs_may_open(state->inode, state->owner->so_cred, open_mode);
			if (ret != 0)
				goto out;
		}
		ret = -EAGAIN;

		/* Try to update the stateid using the delegation */
		if (update_open_stateid(state, NULL, &stateid, fmode))
			goto out_return_state;
	}
out:
	return ERR_PTR(ret);
out_return_state:
	atomic_inc(&state->count);
	return state;
}