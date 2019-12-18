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
struct nfs4_state {TYPE_1__* owner; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  flags; int /*<<< orphan*/  lock_states; } ;
struct nfs4_lock_state {int /*<<< orphan*/  ls_locks; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  fl_owner_t ;
struct TYPE_2__ {int /*<<< orphan*/  so_server; } ;

/* Variables and functions */
 int /*<<< orphan*/  LK_STATE_IN_USE ; 
 struct nfs4_lock_state* __nfs4_find_lock_state (struct nfs4_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct nfs4_lock_state* nfs4_alloc_lock_state (struct nfs4_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  nfs4_free_lock_state (int /*<<< orphan*/ ,struct nfs4_lock_state*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct nfs4_lock_state *nfs4_get_lock_state(struct nfs4_state *state, fl_owner_t owner, pid_t pid, unsigned int type)
{
	struct nfs4_lock_state *lsp, *new = NULL;
	
	for(;;) {
		spin_lock(&state->state_lock);
		lsp = __nfs4_find_lock_state(state, owner, pid, type);
		if (lsp != NULL)
			break;
		if (new != NULL) {
			list_add(&new->ls_locks, &state->lock_states);
			set_bit(LK_STATE_IN_USE, &state->flags);
			lsp = new;
			new = NULL;
			break;
		}
		spin_unlock(&state->state_lock);
		new = nfs4_alloc_lock_state(state, owner, pid, type);
		if (new == NULL)
			return NULL;
	}
	spin_unlock(&state->state_lock);
	if (new != NULL)
		nfs4_free_lock_state(state->owner->so_server, new);
	return lsp;
}