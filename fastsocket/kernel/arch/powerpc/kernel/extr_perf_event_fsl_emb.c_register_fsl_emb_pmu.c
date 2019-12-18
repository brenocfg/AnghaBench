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
struct fsl_emb_pmu {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  PERF_TYPE_RAW ; 
 int /*<<< orphan*/  fsl_emb_pmu ; 
 int /*<<< orphan*/  perf_pmu_register (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct fsl_emb_pmu* ppmu ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 

int register_fsl_emb_pmu(struct fsl_emb_pmu *pmu)
{
	if (ppmu)
		return -EBUSY;		/* something's already registered */

	ppmu = pmu;
	pr_info("%s performance monitor hardware support registered\n",
		pmu->name);

	perf_pmu_register(&fsl_emb_pmu, "cpu", PERF_TYPE_RAW);

	return 0;
}