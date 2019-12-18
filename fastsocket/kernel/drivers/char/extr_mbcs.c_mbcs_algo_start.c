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
union cm_control {int alg_done_int_en; int alg_go; int /*<<< orphan*/  cm_control_reg; } ;
struct algoblock {int /*<<< orphan*/  algoStepCount; int /*<<< orphan*/  intrVector; int /*<<< orphan*/  intrHostDest; int /*<<< orphan*/  amoModType; int /*<<< orphan*/  amoHostDest; } ;
struct mbcs_soft {int /*<<< orphan*/  algolock; int /*<<< orphan*/  algo_done; void* mmr_base; struct algoblock algo; } ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  MBCS_CM_CONTROL ; 
 int /*<<< orphan*/  MBCS_MMR_GET (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBCS_MMR_SET (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbcs_algo_set (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int mbcs_algo_start(struct mbcs_soft *soft)
{
	struct algoblock *algo_soft = &soft->algo;
	void *mmr_base = soft->mmr_base;
	union cm_control cm_control;

	if (mutex_lock_interruptible(&soft->algolock))
		return -ERESTARTSYS;

	atomic_set(&soft->algo_done, 0);

	mbcs_algo_set(mmr_base,
		 algo_soft->amoHostDest,
		 algo_soft->amoModType,
		 algo_soft->intrHostDest,
		 algo_soft->intrVector, algo_soft->algoStepCount);

	/* start algorithm */
	cm_control.cm_control_reg = MBCS_MMR_GET(mmr_base, MBCS_CM_CONTROL);
	cm_control.alg_done_int_en = 1;
	cm_control.alg_go = 1;
	MBCS_MMR_SET(mmr_base, MBCS_CM_CONTROL, cm_control.cm_control_reg);

	mutex_unlock(&soft->algolock);

	return 0;
}