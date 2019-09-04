#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct proc_bsdshortinfo {scalar_t__ pbsi_status; char* pbsi_comm; int /*<<< orphan*/  pbsi_svgid; int /*<<< orphan*/  pbsi_svuid; int /*<<< orphan*/  pbsi_rgid; int /*<<< orphan*/  pbsi_ruid; int /*<<< orphan*/  pbsi_gid; int /*<<< orphan*/  pbsi_uid; int /*<<< orphan*/  pbsi_flags; int /*<<< orphan*/  pbsi_pgid; int /*<<< orphan*/  pbsi_ppid; int /*<<< orphan*/  pbsi_pid; } ;
typedef  TYPE_1__* proc_t ;
struct TYPE_5__ {scalar_t__ p_stat; int p_flag; int p_lflag; scalar_t__ task; int /*<<< orphan*/  p_svgid; int /*<<< orphan*/  p_svuid; int /*<<< orphan*/  p_rgid; int /*<<< orphan*/  p_ruid; int /*<<< orphan*/  p_gid; int /*<<< orphan*/  p_uid; int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pgrpid; int /*<<< orphan*/  p_ppid; int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int MAXCOMLEN ; 
 int PROC_ACTION_STATE (TYPE_1__*) ; 
 int PROC_CONTROL_STATE (TYPE_1__*) ; 
 int /*<<< orphan*/  PROC_FLAG_CONTROLT ; 
 int /*<<< orphan*/  PROC_FLAG_DELAYIDLESLEEP ; 
 int /*<<< orphan*/  PROC_FLAG_EXEC ; 
 int /*<<< orphan*/  PROC_FLAG_INEXIT ; 
 int /*<<< orphan*/  PROC_FLAG_LP64 ; 
 int /*<<< orphan*/  PROC_FLAG_PA_SUSP ; 
 int /*<<< orphan*/  PROC_FLAG_PA_THROTTLE ; 
 int /*<<< orphan*/  PROC_FLAG_PC_KILL ; 
 int /*<<< orphan*/  PROC_FLAG_PC_SUSP ; 
 int /*<<< orphan*/  PROC_FLAG_PC_THROTTLE ; 
 int /*<<< orphan*/  PROC_FLAG_PPWAIT ; 
 int /*<<< orphan*/  PROC_FLAG_PSUGID ; 
 int /*<<< orphan*/  PROC_FLAG_SYSTEM ; 
 int /*<<< orphan*/  PROC_FLAG_THCWD ; 
 int /*<<< orphan*/  PROC_FLAG_TRACED ; 
 int P_CONTROLT ; 
 int P_DELAYIDLESLEEP ; 
 int P_EXEC ; 
 int P_LEXIT ; 
 int P_LP64 ; 
 int P_LPPWAIT ; 
 int P_LTRACED ; 
#define  P_PCKILL 130 
#define  P_PCSUSP 129 
#define  P_PCTHROTTLE 128 
 int P_SUGID ; 
 int P_SYSTEM ; 
 int P_THCWD ; 
 scalar_t__ SZOMB ; 
 scalar_t__ TASK_NULL ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  bzero (struct proc_bsdshortinfo*,int) ; 
 int /*<<< orphan*/  proc_get_darwinbgstate (scalar_t__,int /*<<< orphan*/ *) ; 

int 
proc_pidshortbsdinfo(proc_t p, struct proc_bsdshortinfo * pbsd_shortp, int zombie)
{
	bzero(pbsd_shortp, sizeof(struct proc_bsdshortinfo));
	pbsd_shortp->pbsi_pid = p->p_pid;
	pbsd_shortp->pbsi_ppid = p->p_ppid;
	pbsd_shortp->pbsi_pgid = p->p_pgrpid;
	pbsd_shortp->pbsi_status = p->p_stat;
	bcopy(&p->p_comm, &pbsd_shortp->pbsi_comm[0], MAXCOMLEN);
	pbsd_shortp->pbsi_comm[MAXCOMLEN - 1] = '\0';

	pbsd_shortp->pbsi_flags = 0;	
	if ((p->p_flag & P_SYSTEM) == P_SYSTEM) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_SYSTEM;
	if ((p->p_lflag & P_LTRACED) == P_LTRACED) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_TRACED;
	if ((p->p_lflag & P_LEXIT) == P_LEXIT) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_INEXIT;
	if ((p->p_lflag & P_LPPWAIT) == P_LPPWAIT) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_PPWAIT;
	if ((p->p_flag & P_LP64) == P_LP64) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_LP64;
	if ((p->p_flag & P_CONTROLT) == P_CONTROLT) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_CONTROLT;
	if ((p->p_flag & P_THCWD) == P_THCWD) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_THCWD;
	if ((p->p_flag & P_SUGID) == P_SUGID) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_PSUGID;
	if ((p->p_flag & P_EXEC) == P_EXEC) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_EXEC;
#if !CONFIG_EMBEDDED
	if ((p->p_flag & P_DELAYIDLESLEEP) == P_DELAYIDLESLEEP) 
		pbsd_shortp->pbsi_flags |= PROC_FLAG_DELAYIDLESLEEP;
#endif /* !CONFIG_EMBEDDED */

	switch(PROC_CONTROL_STATE(p)) {
		case P_PCTHROTTLE:
			pbsd_shortp->pbsi_flags |= PROC_FLAG_PC_THROTTLE;
			break;
		case P_PCSUSP:
			pbsd_shortp->pbsi_flags |= PROC_FLAG_PC_SUSP;
			break;
		case P_PCKILL:
			pbsd_shortp->pbsi_flags |= PROC_FLAG_PC_KILL;
			break;
	};

	switch(PROC_ACTION_STATE(p)) {
		case P_PCTHROTTLE:
			pbsd_shortp->pbsi_flags |= PROC_FLAG_PA_THROTTLE;
			break;
		case P_PCSUSP:
			pbsd_shortp->pbsi_flags |= PROC_FLAG_PA_SUSP;
			break;
	};
		
	/* if process is a zombie skip bg state */
	if ((zombie == 0) && (p->p_stat != SZOMB) && (p->task != TASK_NULL))
		proc_get_darwinbgstate(p->task, &pbsd_shortp->pbsi_flags);

	pbsd_shortp->pbsi_uid = p->p_uid;
	pbsd_shortp->pbsi_gid = p->p_gid; 
	pbsd_shortp->pbsi_ruid =  p->p_ruid;
	pbsd_shortp->pbsi_rgid = p->p_rgid;
	pbsd_shortp->pbsi_svuid =  p->p_svuid;
	pbsd_shortp->pbsi_svgid = p->p_svgid;
	
	return(0);
}