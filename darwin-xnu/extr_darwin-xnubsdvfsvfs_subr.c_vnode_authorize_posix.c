#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vauth_ctx ;
struct vnode_attr {int va_mode; int /*<<< orphan*/  va_gid; int /*<<< orphan*/  va_uid; } ;
struct TYPE_9__ {struct vnode_attr* vap; struct vnode_attr* dvap; TYPE_1__* ctx; int /*<<< orphan*/  vp; } ;
struct TYPE_8__ {int /*<<< orphan*/  vc_ucred; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  KAUTH_DEBUG (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char*,char*,int,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int VEXEC ; 
 int VREAD ; 
 int VWRITE ; 
 int /*<<< orphan*/  kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int vauth_dir_ingroup (TYPE_2__*,int*,int) ; 
 scalar_t__ vauth_dir_owner (TYPE_2__*) ; 
 int vauth_file_ingroup (TYPE_2__*,int*,int) ; 
 scalar_t__ vauth_file_owner (TYPE_2__*) ; 
 int /*<<< orphan*/  where ; 

__attribute__((used)) static int
vnode_authorize_posix(vauth_ctx vcp, int action, int on_dir)
{
	struct vnode_attr *vap;
	int needed, error, owner_ok, group_ok, world_ok, ismember;
#ifdef KAUTH_DEBUG_ENABLE
	const char *where = "uninitialized";
# define _SETWHERE(c)	where = c;
#else
# define _SETWHERE(c)
#endif

	/* checking file or directory? */
	if (on_dir) {
		vap = vcp->dvap;
	} else {
		vap = vcp->vap;
	}
	
	error = 0;
	
	/*
	 * We want to do as little work here as possible.  So first we check
	 * which sets of permissions grant us the access we need, and avoid checking
	 * whether specific permissions grant access when more generic ones would.
	 */

	/* owner permissions */
	needed = 0;
	if (action & VREAD)
		needed |= S_IRUSR;
	if (action & VWRITE)
		needed |= S_IWUSR;
	if (action & VEXEC)
		needed |= S_IXUSR;
	owner_ok = (needed & vap->va_mode) == needed;

	/* group permissions */
	needed = 0;
	if (action & VREAD)
		needed |= S_IRGRP;
	if (action & VWRITE)
		needed |= S_IWGRP;
	if (action & VEXEC)
		needed |= S_IXGRP;
	group_ok = (needed & vap->va_mode) == needed;

	/* world permissions */
	needed = 0;
	if (action & VREAD)
		needed |= S_IROTH;
	if (action & VWRITE)
		needed |= S_IWOTH;
	if (action & VEXEC)
		needed |= S_IXOTH;
	world_ok = (needed & vap->va_mode) == needed;

	/* If granted/denied by all three, we're done */
	if (owner_ok && group_ok && world_ok) {
		_SETWHERE("all");
		goto out;
	}
	if (!owner_ok && !group_ok && !world_ok) {
		_SETWHERE("all");
		error = EACCES;
		goto out;
	}

	/* Check ownership (relatively cheap) */
	if ((on_dir && vauth_dir_owner(vcp)) ||
	    (!on_dir && vauth_file_owner(vcp))) {
		_SETWHERE("user");
		if (!owner_ok)
			error = EACCES;
		goto out;
	}

	/* Not owner; if group and world both grant it we're done */
	if (group_ok && world_ok) {
		_SETWHERE("group/world");
		goto out;
	}
	if (!group_ok && !world_ok) {
		_SETWHERE("group/world");
		error = EACCES;
		goto out;
	}

	/* Check group membership (most expensive) */
	ismember = 0;	/* Default to allow, if the target has no group owner */

	/*
	 * In the case we can't get an answer about the user from the call to
	 * vauth_dir_ingroup() or vauth_file_ingroup(), we want to fail on
	 * the side of caution, rather than simply granting access, or we will
	 * fail to correctly implement exclusion groups, so we set the third
	 * parameter on the basis of the state of 'group_ok'.
	 */
	if (on_dir) {
		error = vauth_dir_ingroup(vcp, &ismember, (!group_ok ? EACCES : 0));
	} else {
		error = vauth_file_ingroup(vcp, &ismember, (!group_ok ? EACCES : 0));
	}
	if (error) {
		if (!group_ok)
			ismember = 1;
		error = 0;
	}
	if (ismember) {
		_SETWHERE("group");
		if (!group_ok)
			error = EACCES;
		goto out;
	}

	/* Not owner, not in group, use world result */
	_SETWHERE("world");
	if (!world_ok)
		error = EACCES;

	/* FALLTHROUGH */

out:
	KAUTH_DEBUG("%p    %s - posix %s permissions : need %s%s%s %x have %s%s%s%s%s%s%s%s%s UID = %d file = %d,%d",
	    vcp->vp, (error == 0) ? "ALLOWED" : "DENIED", where,
	    (action & VREAD)  ? "r" : "-",
	    (action & VWRITE) ? "w" : "-",
	    (action & VEXEC)  ? "x" : "-",
	    needed,
	    (vap->va_mode & S_IRUSR) ? "r" : "-",
	    (vap->va_mode & S_IWUSR) ? "w" : "-",
	    (vap->va_mode & S_IXUSR) ? "x" : "-",
	    (vap->va_mode & S_IRGRP) ? "r" : "-",
	    (vap->va_mode & S_IWGRP) ? "w" : "-",
	    (vap->va_mode & S_IXGRP) ? "x" : "-",
	    (vap->va_mode & S_IROTH) ? "r" : "-",
	    (vap->va_mode & S_IWOTH) ? "w" : "-",
	    (vap->va_mode & S_IXOTH) ? "x" : "-",
	    kauth_cred_getuid(vcp->ctx->vc_ucred),
	    on_dir ? vcp->dvap->va_uid : vcp->vap->va_uid,
	    on_dir ? vcp->dvap->va_gid : vcp->vap->va_gid);
	return(error);
}