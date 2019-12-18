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
struct vinfo_stat {int /*<<< orphan*/  vst_size; int /*<<< orphan*/  vst_gid; int /*<<< orphan*/  vst_uid; int /*<<< orphan*/  vst_mode; } ;
struct pshmnode {int /*<<< orphan*/  mapp_addr; struct pshminfo* pinfo; } ;
struct pshminfo {int /*<<< orphan*/ * pshm_name; int /*<<< orphan*/  pshm_length; int /*<<< orphan*/  pshm_gid; int /*<<< orphan*/  pshm_uid; int /*<<< orphan*/  pshm_mode; } ;
struct pshm_info {int /*<<< orphan*/ * pshm_name; int /*<<< orphan*/  pshm_mappaddr; struct vinfo_stat pshm_stat; } ;

/* Variables and functions */
 int EINVAL ; 
 struct pshminfo* PSHMINFO_NULL ; 
 scalar_t__ PSHMNAMLEN ; 
 int /*<<< orphan*/  PSHM_SUBSYS_LOCK () ; 
 int /*<<< orphan*/  PSHM_SUBSYS_UNLOCK () ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bzero (struct vinfo_stat*,int) ; 

int
fill_pshminfo(struct pshmnode * pshm, struct pshm_info * info)
{
	struct pshminfo *pinfo;
	struct vinfo_stat *sb;
	
	PSHM_SUBSYS_LOCK();
	if ((pinfo = pshm->pinfo) == PSHMINFO_NULL){
		PSHM_SUBSYS_UNLOCK();
		return(EINVAL);
	}

	sb = &info->pshm_stat;

	bzero(sb, sizeof(struct vinfo_stat)); 
	sb->vst_mode = pinfo->pshm_mode;
	sb->vst_uid = pinfo->pshm_uid;
	sb->vst_gid = pinfo->pshm_gid;
	sb->vst_size = pinfo->pshm_length;

	info->pshm_mappaddr = pshm->mapp_addr;
	bcopy(&pinfo->pshm_name[0], &info->pshm_name[0], PSHMNAMLEN+1); 

	PSHM_SUBSYS_UNLOCK();
	return(0);
}