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
struct if_dqblk {int dummy; } ;
struct dquot {int dummy; } ;
typedef  int /*<<< orphan*/  qid_t ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  do_get_dqblk (struct dquot*,struct if_dqblk*) ; 
 struct dquot* dqget (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dqput (struct dquot*) ; 

int vfs_get_dqblk(struct super_block *sb, int type, qid_t id,
		  struct if_dqblk *di)
{
	struct dquot *dquot;

	dquot = dqget(sb, id, type);
	if (!dquot)
		return -ESRCH;
	do_get_dqblk(dquot, di);
	dqput(dquot);

	return 0;
}