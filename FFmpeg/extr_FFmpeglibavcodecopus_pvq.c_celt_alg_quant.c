#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum CeltSpread { ____Placeholder_CeltSpread } CeltSpread ;
struct TYPE_3__ {int* qcoeff; int /*<<< orphan*/  (* pvq_search ) (float*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;
typedef  TYPE_1__ CeltPVQ ;

/* Variables and functions */
 int /*<<< orphan*/  celt_encode_pulses (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  celt_exp_rotation (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  celt_extract_collapse_mask (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  celt_normalize_residual (int*,float*,int /*<<< orphan*/ ,float) ; 
 float sqrtf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (float*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t celt_alg_quant(OpusRangeCoder *rc, float *X, uint32_t N, uint32_t K,
                               enum CeltSpread spread, uint32_t blocks, float gain,
                               CeltPVQ *pvq)
{
    int *y = pvq->qcoeff;

    celt_exp_rotation(X, N, blocks, K, spread, 1);
    gain /= sqrtf(pvq->pvq_search(X, y, K, N));
    celt_encode_pulses(rc, y,  N, K);
    celt_normalize_residual(y, X, N, gain);
    celt_exp_rotation(X, N, blocks, K, spread, 0);
    return celt_extract_collapse_mask(y, N, blocks);
}