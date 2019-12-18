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
typedef  scalar_t__ uid_t ;
typedef  int /*<<< orphan*/  u_short ;
struct ipc_perm {int mode; scalar_t__ cuid; scalar_t__ uid; scalar_t__ gid; scalar_t__ cgid; } ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  kauth_cred_t ;

/* Variables and functions */
 int EACCES ; 
 int EPERM ; 
 int IPC_M ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 scalar_t__ kauth_cred_getuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kauth_cred_ismember_gid (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  suser (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ipcperm(kauth_cred_t cred, struct ipc_perm *perm, int mode_req)
{
	uid_t	uid = kauth_cred_getuid(cred);	/* avoid multiple calls */
	int	want_mod_controlinfo = (mode_req & IPC_M);
	int	is_member;
	mode_t	mode_owner = (perm->mode & S_IRWXU);
	mode_t	mode_group = (perm->mode & S_IRWXG) << 3;
	mode_t	mode_world = (perm->mode & S_IRWXO) << 6;

	/* Grant all rights to super user */
	if (!suser(cred, (u_short *)NULL))
		return (0);

	/* Grant or deny rights based on ownership */
	if (uid == perm->cuid || uid == perm->uid) {
		if (want_mod_controlinfo)
			return (0);

		return ((mode_req & mode_owner) == mode_req ? 0 : EACCES);
	} else {
		/* everyone else who wants to modify control info is denied */
		if (want_mod_controlinfo)
			return (EPERM);
	}

	/*
	 * Combined group and world rights check, if no owner rights; positive
	 * asssertion of gid/cgid equality avoids an extra callout in the
	 * common case.
	 */
	if ((mode_req & mode_group & mode_world) == mode_req) {
		return (0);
	} else {
		if ((mode_req & mode_group) != mode_req) {
			if ((!kauth_cred_ismember_gid(cred, perm->gid, &is_member) && is_member) &&
			    ((perm->gid == perm->cgid) ||
			     (!kauth_cred_ismember_gid(cred, perm->cgid, &is_member) && is_member))) {
			    	return (EACCES);
			} else {
				if ((mode_req & mode_world) != mode_req) {
					return (EACCES);
				} else {
					return (0);
				}
			}
		} else {
			if ((!kauth_cred_ismember_gid(cred, perm->gid, &is_member) && is_member) ||
			    ((perm->gid != perm->cgid) &&
			     (!kauth_cred_ismember_gid(cred, perm->cgid, &is_member) && is_member))) {
			    	return (0);
			} else {
				if ((mode_req & mode_world) != mode_req) {
					return (EACCES);
				} else {
					return (0);
				}
			}
		}
	}
}