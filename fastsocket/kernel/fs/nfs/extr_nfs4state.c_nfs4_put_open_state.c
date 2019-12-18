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
struct nfs4_state_owner {int /*<<< orphan*/  so_lock; } ;
struct nfs4_state {int /*<<< orphan*/  open_states; int /*<<< orphan*/  inode_states; int /*<<< orphan*/  count; struct nfs4_state_owner* owner; struct inode* inode; } ;
struct inode {int /*<<< orphan*/  i_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfs4_free_open_state (struct nfs4_state*) ; 
 int /*<<< orphan*/  nfs4_put_state_owner (struct nfs4_state_owner*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void nfs4_put_open_state(struct nfs4_state *state)
{
	struct inode *inode = state->inode;
	struct nfs4_state_owner *owner = state->owner;

	if (!atomic_dec_and_lock(&state->count, &owner->so_lock))
		return;
	spin_lock(&inode->i_lock);
	list_del(&state->inode_states);
	list_del(&state->open_states);
	spin_unlock(&inode->i_lock);
	spin_unlock(&owner->so_lock);
	iput(inode);
	nfs4_free_open_state(state);
	nfs4_put_state_owner(owner);
}