#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  allow; int /*<<< orphan*/  deny; } ;
struct TYPE_14__ {int /*<<< orphan*/  allow; } ;
struct TYPE_16__ {int /*<<< orphan*/  allow; int /*<<< orphan*/  deny; } ;
struct TYPE_9__ {int /*<<< orphan*/  allow; int /*<<< orphan*/  deny; } ;
struct posix_acl_state {TYPE_7__ other; TYPE_6__ mask; TYPE_5__* groups; TYPE_8__ group; TYPE_3__* users; TYPE_1__ owner; scalar_t__ empty; } ;
struct posix_acl_entry {void* e_id; int /*<<< orphan*/  e_perm; int /*<<< orphan*/  e_tag; } ;
struct posix_acl {struct posix_acl_entry* a_entries; } ;
struct TYPE_13__ {int n; TYPE_4__* aces; } ;
struct TYPE_12__ {TYPE_8__ perms; void* uid; } ;
struct TYPE_11__ {int n; TYPE_2__* aces; } ;
struct TYPE_10__ {TYPE_8__ perms; void* uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_GROUP ; 
 int /*<<< orphan*/  ACL_GROUP_OBJ ; 
 int /*<<< orphan*/  ACL_MASK ; 
 int /*<<< orphan*/  ACL_OTHER ; 
 void* ACL_UNDEFINED_ID ; 
 int /*<<< orphan*/  ACL_USER ; 
 int /*<<< orphan*/  ACL_USER_OBJ ; 
 int ENOMEM ; 
 struct posix_acl* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned int NFS4_ACL_TYPE_DEFAULT ; 
 int /*<<< orphan*/  add_to_mask (struct posix_acl_state*,TYPE_8__*) ; 
 int check_deny (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  low_mode_from_nfs4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 struct posix_acl* posix_acl_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_acl_release (struct posix_acl*) ; 

__attribute__((used)) static struct posix_acl *
posix_state_to_acl(struct posix_acl_state *state, unsigned int flags)
{
	struct posix_acl_entry *pace;
	struct posix_acl *pacl;
	int nace;
	int i, error = 0;

	/*
	 * ACLs with no ACEs are treated differently in the inheritable
	 * and effective cases: when there are no inheritable ACEs, we
	 * set a zero-length default posix acl:
	 */
	if (state->empty && (flags & NFS4_ACL_TYPE_DEFAULT)) {
		pacl = posix_acl_alloc(0, GFP_KERNEL);
		return pacl ? pacl : ERR_PTR(-ENOMEM);
	}
	/*
	 * When there are no effective ACEs, the following will end
	 * up setting a 3-element effective posix ACL with all
	 * permissions zero.
	 */
	nace = 4 + state->users->n + state->groups->n;
	pacl = posix_acl_alloc(nace, GFP_KERNEL);
	if (!pacl)
		return ERR_PTR(-ENOMEM);

	pace = pacl->a_entries;
	pace->e_tag = ACL_USER_OBJ;
	error = check_deny(state->owner.deny, 1);
	if (error)
		goto out_err;
	low_mode_from_nfs4(state->owner.allow, &pace->e_perm, flags);
	pace->e_id = ACL_UNDEFINED_ID;

	for (i=0; i < state->users->n; i++) {
		pace++;
		pace->e_tag = ACL_USER;
		error = check_deny(state->users->aces[i].perms.deny, 0);
		if (error)
			goto out_err;
		low_mode_from_nfs4(state->users->aces[i].perms.allow,
					&pace->e_perm, flags);
		pace->e_id = state->users->aces[i].uid;
		add_to_mask(state, &state->users->aces[i].perms);
	}

	pace++;
	pace->e_tag = ACL_GROUP_OBJ;
	error = check_deny(state->group.deny, 0);
	if (error)
		goto out_err;
	low_mode_from_nfs4(state->group.allow, &pace->e_perm, flags);
	pace->e_id = ACL_UNDEFINED_ID;
	add_to_mask(state, &state->group);

	for (i=0; i < state->groups->n; i++) {
		pace++;
		pace->e_tag = ACL_GROUP;
		error = check_deny(state->groups->aces[i].perms.deny, 0);
		if (error)
			goto out_err;
		low_mode_from_nfs4(state->groups->aces[i].perms.allow,
					&pace->e_perm, flags);
		pace->e_id = state->groups->aces[i].uid;
		add_to_mask(state, &state->groups->aces[i].perms);
	}

	pace++;
	pace->e_tag = ACL_MASK;
	low_mode_from_nfs4(state->mask.allow, &pace->e_perm, flags);
	pace->e_id = ACL_UNDEFINED_ID;

	pace++;
	pace->e_tag = ACL_OTHER;
	error = check_deny(state->other.deny, 0);
	if (error)
		goto out_err;
	low_mode_from_nfs4(state->other.allow, &pace->e_perm, flags);
	pace->e_id = ACL_UNDEFINED_ID;

	return pacl;
out_err:
	posix_acl_release(pacl);
	return ERR_PTR(error);
}