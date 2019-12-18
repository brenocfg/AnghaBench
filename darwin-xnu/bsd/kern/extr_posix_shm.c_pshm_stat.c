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
struct stat64 {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;
struct stat {int /*<<< orphan*/  st_size; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_mode; } ;
struct pshmnode {struct pshminfo* pinfo; } ;
struct pshminfo {int /*<<< orphan*/  pshm_length; int /*<<< orphan*/  pshm_gid; int /*<<< orphan*/  pshm_uid; int /*<<< orphan*/  pshm_mode; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pshminfo* PSHMINFO_NULL ; 
 int /*<<< orphan*/  PSHM_SUBSYS_LOCK () ; 
 int /*<<< orphan*/  PSHM_SUBSYS_UNLOCK () ; 
 int /*<<< orphan*/  bzero (struct stat64*,int) ; 
 int /*<<< orphan*/  kauth_cred_get () ; 
 int mac_posixshm_check_stat (int /*<<< orphan*/ ,struct pshminfo*) ; 

int
pshm_stat(struct pshmnode *pnode, void *ub, int isstat64)
{
	struct stat *sb = (struct stat *)0;	/* warning avoidance ; protected by isstat64 */
	struct stat64 * sb64 = (struct stat64 *)0;  /* warning avoidance ; protected by isstat64 */
	struct pshminfo *pinfo;
#if CONFIG_MACF
	int error;
#endif
	
	PSHM_SUBSYS_LOCK();
	if ((pinfo = pnode->pinfo) == PSHMINFO_NULL){
		PSHM_SUBSYS_UNLOCK();
		return(EINVAL);
	}

#if CONFIG_MACF
	error = mac_posixshm_check_stat(kauth_cred_get(), pinfo);
	if (error) {
		PSHM_SUBSYS_UNLOCK();
		return(error);
	}
#endif

	if (isstat64 != 0) {
		sb64 = (struct stat64 *)ub;
		bzero(sb64, sizeof(struct stat64)); 
		sb64->st_mode = pinfo->pshm_mode;
		sb64->st_uid = pinfo->pshm_uid;
		sb64->st_gid = pinfo->pshm_gid;
		sb64->st_size = pinfo->pshm_length;
	} else {
		sb = (struct stat *)ub;
		bzero(sb, sizeof(struct stat)); 
		sb->st_mode = pinfo->pshm_mode;
		sb->st_uid = pinfo->pshm_uid;
		sb->st_gid = pinfo->pshm_gid;
		sb->st_size = pinfo->pshm_length;
	}
	PSHM_SUBSYS_UNLOCK();

	return(0);
}