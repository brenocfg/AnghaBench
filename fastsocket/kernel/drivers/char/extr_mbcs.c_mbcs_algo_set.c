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
union intr_dest {scalar_t__ intr_dest_reg; void* int_vector; void* address; } ;
union dma_amo_dest {scalar_t__ dma_amo_dest_reg; void* dma_amo_mod_type; void* dma_amo_sys_addr; } ;
union algo_step {scalar_t__ algo_step_reg; void* alg_step_cnt; } ;
typedef  void* uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MBCS_ALG_AMO_DEST ; 
 int /*<<< orphan*/  MBCS_ALG_INT_DEST ; 
 int /*<<< orphan*/  MBCS_ALG_STEP ; 
 int /*<<< orphan*/  MBCS_MMR_SET (void*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void mbcs_algo_set(void *mmr,
		     uint64_t amoHostDest,
		     uint64_t amoModType,
		     uint64_t intrHostDest,
		     uint64_t intrVector, uint64_t algoStepCount)
{
	union dma_amo_dest amo_dest;
	union intr_dest intr_dest;
	union algo_step step;

	step.algo_step_reg = 0;
	intr_dest.intr_dest_reg = 0;
	amo_dest.dma_amo_dest_reg = 0;

	amo_dest.dma_amo_sys_addr = amoHostDest;
	amo_dest.dma_amo_mod_type = amoModType;
	MBCS_MMR_SET(mmr, MBCS_ALG_AMO_DEST, amo_dest.dma_amo_dest_reg);

	intr_dest.address = intrHostDest;
	intr_dest.int_vector = intrVector;
	MBCS_MMR_SET(mmr, MBCS_ALG_INT_DEST, intr_dest.intr_dest_reg);

	step.alg_step_cnt = algoStepCount;
	MBCS_MMR_SET(mmr, MBCS_ALG_STEP, step.algo_step_reg);
}