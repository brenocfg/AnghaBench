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
struct v2r0_disk_dqblk {int /*<<< orphan*/  dqb_id; } ;
struct qtree_mem_dqinfo {int dummy; } ;
struct dquot {scalar_t__ dq_id; int /*<<< orphan*/  dq_type; int /*<<< orphan*/  dq_sb; } ;
struct TYPE_2__ {struct qtree_mem_dqinfo* dqi_priv; } ;

/* Variables and functions */
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ qtree_entry_unused (struct qtree_mem_dqinfo*,void*) ; 
 TYPE_1__* sb_dqinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v2r0_is_id(void *dp, struct dquot *dquot)
{
	struct v2r0_disk_dqblk *d = dp;
	struct qtree_mem_dqinfo *info =
			sb_dqinfo(dquot->dq_sb, dquot->dq_type)->dqi_priv;

	if (qtree_entry_unused(info, dp))
		return 0;
	return le32_to_cpu(d->dqb_id) == dquot->dq_id;
}