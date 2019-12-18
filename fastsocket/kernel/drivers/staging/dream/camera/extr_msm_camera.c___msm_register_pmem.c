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
struct msm_sync {int /*<<< orphan*/  stats; int /*<<< orphan*/  frame; } ;
struct msm_pmem_info {int type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MSM_PMEM_AEC_AWB 134 
#define  MSM_PMEM_AF 133 
#define  MSM_PMEM_MAINIMG 132 
#define  MSM_PMEM_OUTPUT1 131 
#define  MSM_PMEM_OUTPUT2 130 
#define  MSM_PMEM_RAW_MAINIMG 129 
#define  MSM_PMEM_THUMBAIL 128 
 int msm_pmem_table_add (int /*<<< orphan*/ *,struct msm_pmem_info*) ; 

__attribute__((used)) static int __msm_register_pmem(struct msm_sync *sync,
		struct msm_pmem_info *pinfo)
{
	int rc = 0;

	switch (pinfo->type) {
	case MSM_PMEM_OUTPUT1:
	case MSM_PMEM_OUTPUT2:
	case MSM_PMEM_THUMBAIL:
	case MSM_PMEM_MAINIMG:
	case MSM_PMEM_RAW_MAINIMG:
		rc = msm_pmem_table_add(&sync->frame, pinfo);
		break;

	case MSM_PMEM_AEC_AWB:
	case MSM_PMEM_AF:
		rc = msm_pmem_table_add(&sync->stats, pinfo);
		break;

	default:
		rc = -EINVAL;
		break;
	}

	return rc;
}