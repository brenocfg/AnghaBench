#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_1__* s_qcop; } ;
typedef  scalar_t__ qid_t ;
struct TYPE_2__ {int /*<<< orphan*/  quota_sync; int /*<<< orphan*/  get_dqblk; int /*<<< orphan*/  set_dqblk; int /*<<< orphan*/  get_info; int /*<<< orphan*/  set_info; int /*<<< orphan*/  quota_off; int /*<<< orphan*/  quota_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int EPERM ; 
 int ESRCH ; 
 int GRPQUOTA ; 
 int MAXQUOTAS ; 
#define  Q_GETFMT 135 
#define  Q_GETINFO 134 
#define  Q_GETQUOTA 133 
#define  Q_QUOTAOFF 132 
#define  Q_QUOTAON 131 
#define  Q_SETINFO 130 
#define  Q_SETQUOTA 129 
#define  Q_SYNC 128 
 int USRQUOTA ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_euid () ; 
 int /*<<< orphan*/  in_egroup_p (scalar_t__) ; 
 int /*<<< orphan*/  sb_has_quota_active (struct super_block*,int) ; 

__attribute__((used)) static int generic_quotactl_valid(struct super_block *sb, int type, int cmd,
				  qid_t id)
{
	if (type >= MAXQUOTAS)
		return -EINVAL;
	if (!sb && cmd != Q_SYNC)
		return -ENODEV;
	/* Is operation supported? */
	if (sb && !sb->s_qcop)
		return -ENOSYS;

	switch (cmd) {
		case Q_GETFMT:
			break;
		case Q_QUOTAON:
			if (!sb->s_qcop->quota_on)
				return -ENOSYS;
			break;
		case Q_QUOTAOFF:
			if (!sb->s_qcop->quota_off)
				return -ENOSYS;
			break;
		case Q_SETINFO:
			if (!sb->s_qcop->set_info)
				return -ENOSYS;
			break;
		case Q_GETINFO:
			if (!sb->s_qcop->get_info)
				return -ENOSYS;
			break;
		case Q_SETQUOTA:
			if (!sb->s_qcop->set_dqblk)
				return -ENOSYS;
			break;
		case Q_GETQUOTA:
			if (!sb->s_qcop->get_dqblk)
				return -ENOSYS;
			break;
		case Q_SYNC:
			if (sb && !sb->s_qcop->quota_sync)
				return -ENOSYS;
			break;
		default:
			return -EINVAL;
	}

	/* Is quota turned on for commands which need it? */
	switch (cmd) {
		case Q_GETFMT:
		case Q_GETINFO:
		case Q_SETINFO:
		case Q_SETQUOTA:
		case Q_GETQUOTA:
			/* This is just an informative test so we are satisfied
			 * without the lock */
			if (!sb_has_quota_active(sb, type))
				return -ESRCH;
	}

	/* Check privileges */
	if (cmd == Q_GETQUOTA) {
		if (((type == USRQUOTA && current_euid() != id) ||
		     (type == GRPQUOTA && !in_egroup_p(id))) &&
		    !capable(CAP_SYS_ADMIN))
			return -EPERM;
	}
	else if (cmd != Q_GETFMT && cmd != Q_SYNC && cmd != Q_GETINFO)
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;

	return 0;
}