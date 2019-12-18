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
struct super_block {int dummy; } ;
struct cred {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FILESYSTEM__QUOTAGET ; 
 int /*<<< orphan*/  FILESYSTEM__QUOTAMOD ; 
#define  Q_GETFMT 135 
#define  Q_GETINFO 134 
#define  Q_GETQUOTA 133 
#define  Q_QUOTAOFF 132 
#define  Q_QUOTAON 131 
#define  Q_SETINFO 130 
#define  Q_SETQUOTA 129 
#define  Q_SYNC 128 
 struct cred* current_cred () ; 
 int superblock_has_perm (struct cred const*,struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int selinux_quotactl(int cmds, int type, int id, struct super_block *sb)
{
	const struct cred *cred = current_cred();
	int rc = 0;

	if (!sb)
		return 0;

	switch (cmds) {
	case Q_SYNC:
	case Q_QUOTAON:
	case Q_QUOTAOFF:
	case Q_SETINFO:
	case Q_SETQUOTA:
		rc = superblock_has_perm(cred, sb, FILESYSTEM__QUOTAMOD, NULL);
		break;
	case Q_GETFMT:
	case Q_GETINFO:
	case Q_GETQUOTA:
		rc = superblock_has_perm(cred, sb, FILESYSTEM__QUOTAGET, NULL);
		break;
	default:
		rc = 0;  /* let the kernel handle invalid cmds */
		break;
	}
	return rc;
}