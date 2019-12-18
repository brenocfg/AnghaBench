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
typedef  int /*<<< orphan*/  qid_t ;

/* Variables and functions */
 scalar_t__ XQM_COMMAND (int) ; 
 int generic_quotactl_valid (struct super_block*,int,int,int /*<<< orphan*/ ) ; 
 int security_quotactl (int,int,int /*<<< orphan*/ ,struct super_block*) ; 
 int xqm_quotactl_valid (struct super_block*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_quotactl_valid(struct super_block *sb, int type, int cmd,
				qid_t id)
{
	int error;

	if (XQM_COMMAND(cmd))
		error = xqm_quotactl_valid(sb, type, cmd, id);
	else
		error = generic_quotactl_valid(sb, type, cmd, id);
	if (!error)
		error = security_quotactl(cmd, type, id, sb);
	return error;
}