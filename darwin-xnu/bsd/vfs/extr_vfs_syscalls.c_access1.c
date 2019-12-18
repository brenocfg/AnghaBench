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
typedef  int /*<<< orphan*/  vnode_t ;
typedef  int /*<<< orphan*/  vfs_context_t ;
typedef  int kauth_action_t ;

/* Variables and functions */
 int KAUTH_VNODE_ACCESS ; 
 int KAUTH_VNODE_ADD_FILE ; 
 int KAUTH_VNODE_ADD_SUBDIRECTORY ; 
 int KAUTH_VNODE_EXECUTE ; 
 int KAUTH_VNODE_READ_DATA ; 
 int KAUTH_VNODE_SEARCH ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int R_OK ; 
 int W_OK ; 
 int X_OK ; 
 int _ACCESS_EXTENDED_MASK ; 
 int mac_vnode_check_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vnode_authorize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isdir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
access1(vnode_t vp, vnode_t dvp, int uflags, vfs_context_t ctx)
{
 	kauth_action_t action;
	int error;

 	/*
 	 * If just the regular access bits, convert them to something
	 * that vnode_authorize will understand.
 	 */
 	if (!(uflags & _ACCESS_EXTENDED_MASK)) {
 		action = 0;
  		if (uflags & R_OK)
			action |= KAUTH_VNODE_READ_DATA;	/* aka KAUTH_VNODE_LIST_DIRECTORY */
  		if (uflags & W_OK) {
			if (vnode_isdir(vp)) {
				action |= KAUTH_VNODE_ADD_FILE |
				    KAUTH_VNODE_ADD_SUBDIRECTORY;
				/* might want delete rights here too */
			} else {
				action |= KAUTH_VNODE_WRITE_DATA;
			}
		}
  		if (uflags & X_OK) {
			if (vnode_isdir(vp)) {
				action |= KAUTH_VNODE_SEARCH;
			} else {
				action |= KAUTH_VNODE_EXECUTE;
			}
		}
  	} else {
		/* take advantage of definition of uflags */
		action = uflags >> 8;
	}

#if CONFIG_MACF
	error = mac_vnode_check_access(ctx, vp, uflags);
	if (error)
		return (error);
#endif /* MAC */

 	/* action == 0 means only check for existence */
 	if (action != 0) {
 		error = vnode_authorize(vp, dvp, action | KAUTH_VNODE_ACCESS, ctx);
	} else {
		error = 0;
	}

	return(error);
}