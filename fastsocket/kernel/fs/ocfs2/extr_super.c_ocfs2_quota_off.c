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

/* Variables and functions */
 int /*<<< orphan*/  DQUOT_LIMITS_ENABLED ; 
 int vfs_quota_disable (struct super_block*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_quota_off(struct super_block *sb, int type, int remount)
{
	if (remount)
		return 0;	/* Ignore now and handle later in
				 * ocfs2_remount() */
	return vfs_quota_disable(sb, type, DQUOT_LIMITS_ENABLED);
}