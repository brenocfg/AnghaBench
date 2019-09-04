#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  scalar_t__ kauth_action_t ;
struct TYPE_3__ {int ks_flags; } ;

/* Variables and functions */
 scalar_t__ KAUTH_FILEOP_CLOSE ; 
 scalar_t__ KAUTH_FILEOP_EXEC ; 
 scalar_t__ KAUTH_FILEOP_OPEN ; 
 scalar_t__ KAUTH_FILEOP_WILL_RENAME ; 
 int KS_F_HAS_LISTENERS ; 
 int MAXPATHLEN ; 
 char* get_pathbuff () ; 
 int /*<<< orphan*/  kauth_authorize_action (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,uintptr_t,uintptr_t,uintptr_t,int /*<<< orphan*/ ) ; 
 TYPE_1__* kauth_scope_fileop ; 
 int /*<<< orphan*/  release_pathbuff (char*) ; 
 scalar_t__ vn_getpath (int /*<<< orphan*/ ,char*,int*) ; 

int
kauth_authorize_fileop(kauth_cred_t credential, kauth_action_t action, uintptr_t arg0, uintptr_t arg1)
{
	char 		*namep = NULL;
	int			name_len;
	uintptr_t	arg2 = 0;
	
	/* we do not have a primary handler for the fileop scope so bail out if 
	 * there are no listeners.
	 */
	if ((kauth_scope_fileop->ks_flags & KS_F_HAS_LISTENERS) == 0) {
		return(0);
	}

	if (action == KAUTH_FILEOP_OPEN ||
	    action == KAUTH_FILEOP_CLOSE ||
	    action == KAUTH_FILEOP_EXEC ||
	    action == KAUTH_FILEOP_WILL_RENAME) {
		/* get path to the given vnode as a convenience to our listeners.
		 */
		namep = get_pathbuff();
		name_len = MAXPATHLEN;
		if (vn_getpath((vnode_t)arg0, namep, &name_len) != 0) {
			release_pathbuff(namep);
			return(0);
		}
		if (action == KAUTH_FILEOP_CLOSE ||
		    action == KAUTH_FILEOP_WILL_RENAME) {
			/*
			 * - Close has some flags that come in via arg1.
			 * - Will-rename wants to pass the vnode and
			 *   both paths to the listeners ("to" path
			 *   starts in arg1, moves to arg2).
			 */
			arg2 = arg1;
		}
		arg1 = (uintptr_t)namep;
	}	
	kauth_authorize_action(kauth_scope_fileop, credential, action, arg0, arg1, arg2, 0);
	
	if (namep != NULL) {
		release_pathbuff(namep);
	}
	
	return(0);
}