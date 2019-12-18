#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nfs_inode {int /*<<< orphan*/  open_states; } ;
struct nfs4_state_owner {int /*<<< orphan*/  so_lock; int /*<<< orphan*/  so_states; int /*<<< orphan*/  so_count; } ;
struct nfs4_state {int /*<<< orphan*/  open_states; int /*<<< orphan*/  inode; int /*<<< orphan*/  inode_states; struct nfs4_state_owner* owner; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 struct nfs4_state* __nfs4_find_state_byowner (struct inode*,struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igrab (struct inode*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs4_state* nfs4_alloc_open_state () ; 
 int /*<<< orphan*/  nfs4_free_open_state (struct nfs4_state*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct nfs4_state *
nfs4_get_open_state(struct inode *inode, struct nfs4_state_owner *owner)
{
	struct nfs4_state *state, *new;
	struct nfs_inode *nfsi = NFS_I(inode);

	spin_lock(&inode->i_lock);
	state = __nfs4_find_state_byowner(inode, owner);
	spin_unlock(&inode->i_lock);
	if (state)
		goto out;
	new = nfs4_alloc_open_state();
	spin_lock(&owner->so_lock);
	spin_lock(&inode->i_lock);
	state = __nfs4_find_state_byowner(inode, owner);
	if (state == NULL && new != NULL) {
		state = new;
		state->owner = owner;
		atomic_inc(&owner->so_count);
		list_add(&state->inode_states, &nfsi->open_states);
		state->inode = igrab(inode);
		spin_unlock(&inode->i_lock);
		/* Note: The reclaim code dictates that we add stateless
		 * and read-only stateids to the end of the list */
		list_add_tail(&state->open_states, &owner->so_states);
		spin_unlock(&owner->so_lock);
	} else {
		spin_unlock(&inode->i_lock);
		spin_unlock(&owner->so_lock);
		if (new)
			nfs4_free_open_state(new);
	}
out:
	return state;
}