#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* vauth_ctx ;
struct vnode_attr {TYPE_2__* va_acl; } ;
struct kauth_acl_eval {int ae_requested; int ae_result; int ae_residual; int /*<<< orphan*/  ae_found_deny; int /*<<< orphan*/  ae_exp_gexec; int /*<<< orphan*/  ae_exp_gwrite; int /*<<< orphan*/  ae_exp_gread; int /*<<< orphan*/  ae_exp_gall; int /*<<< orphan*/  ae_options; int /*<<< orphan*/  ae_count; int /*<<< orphan*/ * ae_acl; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;
typedef  int kauth_ace_rights_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {int /*<<< orphan*/  vp; TYPE_1__* ctx; struct vnode_attr* vap; } ;
struct TYPE_9__ {int /*<<< orphan*/  acl_entrycount; int /*<<< orphan*/ * acl_ace; } ;
struct TYPE_8__ {int /*<<< orphan*/  vc_ucred; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOENT ; 
 int /*<<< orphan*/  KAUTH_AEVAL_IN_GROUP ; 
 int /*<<< orphan*/  KAUTH_AEVAL_IN_GROUP_UNKNOWN ; 
 int /*<<< orphan*/  KAUTH_AEVAL_IS_OWNER ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int /*<<< orphan*/ ,...) ; 
#define  KAUTH_RESULT_ALLOW 130 
#define  KAUTH_RESULT_DEFER 129 
#define  KAUTH_RESULT_DENY 128 
 int KAUTH_VNODE_ADD_FILE ; 
 int KAUTH_VNODE_ADD_SUBDIRECTORY ; 
 int KAUTH_VNODE_APPEND_DATA ; 
 int KAUTH_VNODE_CHANGE_OWNER ; 
 int KAUTH_VNODE_CHECKIMMUTABLE ; 
 int KAUTH_VNODE_DELETE ; 
 int KAUTH_VNODE_DELETE_CHILD ; 
 int KAUTH_VNODE_EXECUTE ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_ALL_BITS ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_EXECUTE_BITS ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_READ_BITS ; 
 int /*<<< orphan*/  KAUTH_VNODE_GENERIC_WRITE_BITS ; 
 int KAUTH_VNODE_LIST_DIRECTORY ; 
 int KAUTH_VNODE_READ_ATTRIBUTES ; 
 int KAUTH_VNODE_READ_DATA ; 
 int KAUTH_VNODE_READ_EXTATTRIBUTES ; 
 int KAUTH_VNODE_READ_SECURITY ; 
 int KAUTH_VNODE_SEARCH ; 
 int KAUTH_VNODE_TAKE_OWNERSHIP ; 
 int KAUTH_VNODE_WRITE_ATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_DATA ; 
 int KAUTH_VNODE_WRITE_EXTATTRIBUTES ; 
 int KAUTH_VNODE_WRITE_SECURITY ; 
 scalar_t__ VATTR_IS_NOT (struct vnode_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VEXEC ; 
 int /*<<< orphan*/  VREAD ; 
 int /*<<< orphan*/  VWRITE ; 
 int kauth_acl_evaluate (int /*<<< orphan*/ ,struct kauth_acl_eval*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  va_acl ; 
 int vauth_file_ingroup (TYPE_3__*,int*,int) ; 
 scalar_t__ vauth_file_owner (TYPE_3__*) ; 
 int vnode_authorize_posix (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vnode_isdir (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vnode_authorize_simple(vauth_ctx vcp, kauth_ace_rights_t acl_rights, kauth_ace_rights_t preauth_rights, boolean_t *found_deny)
{
	struct vnode_attr	*vap = vcp->vap;
	kauth_cred_t		cred = vcp->ctx->vc_ucred;
	struct kauth_acl_eval	eval;
	int			error, ismember;
	mode_t			posix_action;

	/*
	 * If we are the file owner, we automatically have some rights.
	 *
	 * Do we need to expand this to support group ownership?
	 */
	if (vauth_file_owner(vcp))
		acl_rights &= ~(KAUTH_VNODE_WRITE_SECURITY);

	/*
	 * If we are checking both TAKE_OWNERSHIP and WRITE_SECURITY, we can
	 * mask the latter.  If TAKE_OWNERSHIP is requested the caller is about to
	 * change ownership to themselves, and WRITE_SECURITY is implicitly
	 * granted to the owner.  We need to do this because at this point
	 * WRITE_SECURITY may not be granted as the caller is not currently
	 * the owner.
	 */
	if ((acl_rights & KAUTH_VNODE_TAKE_OWNERSHIP) &&
	    (acl_rights & KAUTH_VNODE_WRITE_SECURITY))
		acl_rights &= ~KAUTH_VNODE_WRITE_SECURITY;
	
	if (acl_rights == 0) {
		KAUTH_DEBUG("%p    ALLOWED - implicit or no rights required", vcp->vp);
		return(0);
	}

	/* if we have an ACL, evaluate it */
	if (VATTR_IS_NOT(vap, va_acl, NULL)) {
		eval.ae_requested = acl_rights;
		eval.ae_acl = &vap->va_acl->acl_ace[0];
		eval.ae_count = vap->va_acl->acl_entrycount;
		eval.ae_options = 0;
		if (vauth_file_owner(vcp))
			eval.ae_options |= KAUTH_AEVAL_IS_OWNER;
		/*
		 * We use ENOENT as a marker to indicate we could not get
		 * information in order to delay evaluation until after we
		 * have the ACL evaluation answer.  Previously, we would
		 * always deny the operation at this point.
		 */
		if ((error = vauth_file_ingroup(vcp, &ismember, ENOENT)) != 0 && error != ENOENT)
			return(error);
		if (error == ENOENT)
			eval.ae_options |= KAUTH_AEVAL_IN_GROUP_UNKNOWN;
		else if (ismember)
			eval.ae_options |= KAUTH_AEVAL_IN_GROUP;
		eval.ae_exp_gall = KAUTH_VNODE_GENERIC_ALL_BITS;
		eval.ae_exp_gread = KAUTH_VNODE_GENERIC_READ_BITS;
		eval.ae_exp_gwrite = KAUTH_VNODE_GENERIC_WRITE_BITS;
		eval.ae_exp_gexec = KAUTH_VNODE_GENERIC_EXECUTE_BITS;
		
		if ((error = kauth_acl_evaluate(cred, &eval)) != 0) {
			KAUTH_DEBUG("%p    ERROR during ACL processing - %d", vcp->vp, error);
			return(error);
		}
		
		switch(eval.ae_result) {
		case KAUTH_RESULT_DENY:
			KAUTH_DEBUG("%p    DENIED - by ACL", vcp->vp);
			return(EACCES);		/* deny, deny, counter-allege */
		case KAUTH_RESULT_ALLOW:
			KAUTH_DEBUG("%p    ALLOWED - all rights granted by ACL", vcp->vp);
			return(0);
		case KAUTH_RESULT_DEFER:
		default:
			/* Effectively the same as !delete_child_denied */
			KAUTH_DEBUG("%p    DEFERRED - directory ACL", vcp->vp);
			break;
		}

		*found_deny = eval.ae_found_deny;

		/* fall through and evaluate residual rights */
	} else {
		/* no ACL, everything is residual */
		eval.ae_residual = acl_rights;
	}

	/*
	 * Grant residual rights that have been pre-authorized.
	 */
	eval.ae_residual &= ~preauth_rights;

	/*
	 * We grant WRITE_ATTRIBUTES to the owner if it hasn't been denied.
	 */
	if (vauth_file_owner(vcp))
		eval.ae_residual &= ~KAUTH_VNODE_WRITE_ATTRIBUTES;
	
	if (eval.ae_residual == 0) {
		KAUTH_DEBUG("%p    ALLOWED - rights already authorized", vcp->vp);
		return(0);
	}		
	
	/*
	 * Bail if we have residual rights that can't be granted by posix permissions,
	 * or aren't presumed granted at this point.
	 *
	 * XXX these can be collapsed for performance
	 */
	if (eval.ae_residual & KAUTH_VNODE_CHANGE_OWNER) {
		KAUTH_DEBUG("%p    DENIED - CHANGE_OWNER not permitted", vcp->vp);
		return(EACCES);
	}
	if (eval.ae_residual & KAUTH_VNODE_WRITE_SECURITY) {
		KAUTH_DEBUG("%p    DENIED - WRITE_SECURITY not permitted", vcp->vp);
		return(EACCES);
	}

#if DIAGNOSTIC
	if (eval.ae_residual & KAUTH_VNODE_DELETE)
		panic("vnode_authorize: can't be checking delete permission here");
#endif

	/*
	 * Compute the fallback posix permissions that will satisfy the remaining
	 * rights.
	 */
	posix_action = 0;
	if (eval.ae_residual & (KAUTH_VNODE_READ_DATA |
		KAUTH_VNODE_LIST_DIRECTORY |
		KAUTH_VNODE_READ_EXTATTRIBUTES))
		posix_action |= VREAD;
	if (eval.ae_residual & (KAUTH_VNODE_WRITE_DATA |
		KAUTH_VNODE_ADD_FILE |
		KAUTH_VNODE_ADD_SUBDIRECTORY |
		KAUTH_VNODE_DELETE_CHILD |
		KAUTH_VNODE_WRITE_ATTRIBUTES |
		KAUTH_VNODE_WRITE_EXTATTRIBUTES))
		posix_action |= VWRITE;
	if (eval.ae_residual & (KAUTH_VNODE_EXECUTE |
		KAUTH_VNODE_SEARCH))
		posix_action |= VEXEC;
	
	if (posix_action != 0) {
		return(vnode_authorize_posix(vcp, posix_action, 0 /* !on_dir */));
	} else {
		KAUTH_DEBUG("%p    ALLOWED - residual rights %s%s%s%s%s%s%s%s%s%s%s%s%s%s granted due to no posix mapping",
		    vcp->vp,
		    (eval.ae_residual & KAUTH_VNODE_READ_DATA)
		    ? vnode_isdir(vcp->vp) ? " LIST_DIRECTORY" : " READ_DATA" : "",
		    (eval.ae_residual & KAUTH_VNODE_WRITE_DATA)
		    ? vnode_isdir(vcp->vp) ? " ADD_FILE" : " WRITE_DATA" : "",
		    (eval.ae_residual & KAUTH_VNODE_EXECUTE)
		    ? vnode_isdir(vcp->vp) ? " SEARCH" : " EXECUTE" : "",
		    (eval.ae_residual & KAUTH_VNODE_DELETE)
		    ? " DELETE" : "",
		    (eval.ae_residual & KAUTH_VNODE_APPEND_DATA)
		    ? vnode_isdir(vcp->vp) ? " ADD_SUBDIRECTORY" : " APPEND_DATA" : "",
		    (eval.ae_residual & KAUTH_VNODE_DELETE_CHILD)
		    ? " DELETE_CHILD" : "",
		    (eval.ae_residual & KAUTH_VNODE_READ_ATTRIBUTES)
		    ? " READ_ATTRIBUTES" : "",
		    (eval.ae_residual & KAUTH_VNODE_WRITE_ATTRIBUTES)
		    ? " WRITE_ATTRIBUTES" : "",
		    (eval.ae_residual & KAUTH_VNODE_READ_EXTATTRIBUTES)
		    ? " READ_EXTATTRIBUTES" : "",
		    (eval.ae_residual & KAUTH_VNODE_WRITE_EXTATTRIBUTES)
		    ? " WRITE_EXTATTRIBUTES" : "",
		    (eval.ae_residual & KAUTH_VNODE_READ_SECURITY)
		    ? " READ_SECURITY" : "",
		    (eval.ae_residual & KAUTH_VNODE_WRITE_SECURITY)
		    ? " WRITE_SECURITY" : "",
		    (eval.ae_residual & KAUTH_VNODE_CHECKIMMUTABLE)
		    ? " CHECKIMMUTABLE" : "",
		    (eval.ae_residual & KAUTH_VNODE_CHANGE_OWNER)
		    ? " CHANGE_OWNER" : "");
	}

	/*
	 * Lack of required Posix permissions implies no reason to deny access.
	 */
	return(0);
}