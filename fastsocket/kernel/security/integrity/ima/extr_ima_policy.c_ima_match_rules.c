#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct task_struct {TYPE_2__* cred; } ;
struct inode {TYPE_1__* i_sb; } ;
struct ima_measure_rule_entry {int flags; int func; int mask; scalar_t__ fsmagic; scalar_t__ uid; TYPE_3__* lsm; } ;
typedef  enum ima_hooks { ____Placeholder_ima_hooks } ima_hooks ;
struct TYPE_6__ {int /*<<< orphan*/  rule; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ uid; } ;
struct TYPE_4__ {scalar_t__ s_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  Audit_equal ; 
 int IMA_FSMAGIC ; 
 int IMA_FUNC ; 
 int IMA_MASK ; 
 int IMA_UID ; 
#define  LSM_OBJ_ROLE 133 
#define  LSM_OBJ_TYPE 132 
#define  LSM_OBJ_USER 131 
#define  LSM_SUBJ_ROLE 130 
#define  LSM_SUBJ_TYPE 129 
#define  LSM_SUBJ_USER 128 
 int MAX_LSM_RULES ; 
 struct task_struct* current ; 
 int security_filter_rule_match (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_inode_getsecid (struct inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  security_task_getsecid (struct task_struct*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ima_match_rules(struct ima_measure_rule_entry *rule,
			    struct inode *inode, enum ima_hooks func, int mask)
{
	struct task_struct *tsk = current;
	int i;

	if ((rule->flags & IMA_FUNC) && rule->func != func)
		return false;
	if ((rule->flags & IMA_MASK) && rule->mask != mask)
		return false;
	if ((rule->flags & IMA_FSMAGIC)
	    && rule->fsmagic != inode->i_sb->s_magic)
		return false;
	if ((rule->flags & IMA_UID) && rule->uid != tsk->cred->uid)
		return false;
	for (i = 0; i < MAX_LSM_RULES; i++) {
		int rc = 0;
		u32 osid, sid;

		if (!rule->lsm[i].rule)
			continue;

		switch (i) {
		case LSM_OBJ_USER:
		case LSM_OBJ_ROLE:
		case LSM_OBJ_TYPE:
			security_inode_getsecid(inode, &osid);
			rc = security_filter_rule_match(osid,
							rule->lsm[i].type,
							Audit_equal,
							rule->lsm[i].rule,
							NULL);
			break;
		case LSM_SUBJ_USER:
		case LSM_SUBJ_ROLE:
		case LSM_SUBJ_TYPE:
			security_task_getsecid(tsk, &sid);
			rc = security_filter_rule_match(sid,
							rule->lsm[i].type,
							Audit_equal,
							rule->lsm[i].rule,
							NULL);
		default:
			break;
		}
		if (!rc)
			return false;
	}
	return true;
}