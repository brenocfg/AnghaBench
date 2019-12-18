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
struct TYPE_2__ {int /*<<< orphan*/  quota_sync; int /*<<< orphan*/  get_xquota; int /*<<< orphan*/  set_xquota; int /*<<< orphan*/  get_xstate; int /*<<< orphan*/  set_xstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int EPERM ; 
#define  Q_XGETQSTAT 134 
#define  Q_XGETQUOTA 133 
#define  Q_XQUOTAOFF 132 
#define  Q_XQUOTAON 131 
#define  Q_XQUOTARM 130 
#define  Q_XQUOTASYNC 129 
#define  Q_XSETQLIM 128 
 int XQM_GRPQUOTA ; 
 int XQM_MAXQUOTAS ; 
 int XQM_USRQUOTA ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ current_euid () ; 
 int /*<<< orphan*/  in_egroup_p (scalar_t__) ; 

__attribute__((used)) static int xqm_quotactl_valid(struct super_block *sb, int type, int cmd,
			      qid_t id)
{
	if (type >= XQM_MAXQUOTAS)
		return -EINVAL;
	if (!sb)
		return -ENODEV;
	if (!sb->s_qcop)
		return -ENOSYS;

	switch (cmd) {
		case Q_XQUOTAON:
		case Q_XQUOTAOFF:
		case Q_XQUOTARM:
			if (!sb->s_qcop->set_xstate)
				return -ENOSYS;
			break;
		case Q_XGETQSTAT:
			if (!sb->s_qcop->get_xstate)
				return -ENOSYS;
			break;
		case Q_XSETQLIM:
			if (!sb->s_qcop->set_xquota)
				return -ENOSYS;
			break;
		case Q_XGETQUOTA:
			if (!sb->s_qcop->get_xquota)
				return -ENOSYS;
			break;
		case Q_XQUOTASYNC:
			if (!sb->s_qcop->quota_sync)
				return -ENOSYS;
			break;
		default:
			return -EINVAL;
	}

	/* Check privileges */
	if (cmd == Q_XGETQUOTA) {
		if (((type == XQM_USRQUOTA && current_euid() != id) ||
		     (type == XQM_GRPQUOTA && !in_egroup_p(id))) &&
		     !capable(CAP_SYS_ADMIN))
			return -EPERM;
	} else if (cmd != Q_XGETQSTAT && cmd != Q_XQUOTASYNC) {
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
	}

	return 0;
}