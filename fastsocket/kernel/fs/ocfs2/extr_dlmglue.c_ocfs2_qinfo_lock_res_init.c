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
struct TYPE_2__ {int /*<<< orphan*/  dqi_sb; int /*<<< orphan*/  dqi_type; } ;
struct ocfs2_mem_dqinfo {TYPE_1__ dqi_gi; } ;
struct ocfs2_lock_res {int /*<<< orphan*/  l_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OCFS2_LOCK_TYPE_QINFO ; 
 int /*<<< orphan*/  OCFS2_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_build_lock_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_common (int /*<<< orphan*/ ,struct ocfs2_lock_res*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ocfs2_mem_dqinfo*) ; 
 int /*<<< orphan*/  ocfs2_lock_res_init_once (struct ocfs2_lock_res*) ; 
 int /*<<< orphan*/  ocfs2_qinfo_lops ; 

void ocfs2_qinfo_lock_res_init(struct ocfs2_lock_res *lockres,
			       struct ocfs2_mem_dqinfo *info)
{
	ocfs2_lock_res_init_once(lockres);
	ocfs2_build_lock_name(OCFS2_LOCK_TYPE_QINFO, info->dqi_gi.dqi_type,
			      0, lockres->l_name);
	ocfs2_lock_res_init_common(OCFS2_SB(info->dqi_gi.dqi_sb), lockres,
				   OCFS2_LOCK_TYPE_QINFO, &ocfs2_qinfo_lops,
				   info);
}