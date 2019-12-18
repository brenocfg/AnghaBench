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
struct nfs_lockowner {int /*<<< orphan*/  l_pid; int /*<<< orphan*/  l_owner; } ;
struct nfs4_state {int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct nfs4_lock_state {int ls_flags; TYPE_1__ ls_sequence; int /*<<< orphan*/  ls_stateid; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  nfs4_stateid ;
typedef  int /*<<< orphan*/  fl_owner_t ;

/* Variables and functions */
 int ENOENT ; 
 int EWOULDBLOCK ; 
 int /*<<< orphan*/  LK_STATE_IN_USE ; 
 int /*<<< orphan*/  NFS4_ANY_LOCK_TYPE ; 
 int NFS_LOCK_INITIALIZED ; 
 struct nfs4_lock_state* __nfs4_find_lock_state (struct nfs4_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_put_lock_state (struct nfs4_lock_state*) ; 
 int /*<<< orphan*/  nfs4_stateid_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs4_copy_lock_stateid(nfs4_stateid *dst,
		struct nfs4_state *state,
		const struct nfs_lockowner *lockowner)
{
	struct nfs4_lock_state *lsp;
	fl_owner_t fl_owner;
	pid_t fl_pid;
	int ret = -ENOENT;


	if (lockowner == NULL)
		goto out;

	if (test_bit(LK_STATE_IN_USE, &state->flags) == 0)
		goto out;

	fl_owner = lockowner->l_owner;
	fl_pid = lockowner->l_pid;
	spin_lock(&state->state_lock);
	lsp = __nfs4_find_lock_state(state, fl_owner, fl_pid, NFS4_ANY_LOCK_TYPE);
	if (lsp != NULL && (lsp->ls_flags & NFS_LOCK_INITIALIZED) != 0) {
		nfs4_stateid_copy(dst, &lsp->ls_stateid);
		ret = 0;
		smp_rmb();
		if (!list_empty(&lsp->ls_sequence.list))
			ret = -EWOULDBLOCK;
	}
	spin_unlock(&state->state_lock);
	nfs4_put_lock_state(lsp);
out:
	return ret;
}