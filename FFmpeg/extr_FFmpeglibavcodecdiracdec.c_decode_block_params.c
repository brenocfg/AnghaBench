#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ ** mv; int /*<<< orphan*/ * dc; } ;
struct TYPE_13__ {int ref; TYPE_1__ u; } ;
struct TYPE_12__ {int num_refs; scalar_t__ globalmc_flag; } ;
typedef  TYPE_2__ DiracContext ;
typedef  TYPE_3__ DiracBlock ;
typedef  int /*<<< orphan*/  DiracArith ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_DC_DATA ; 
 int /*<<< orphan*/  CTX_DC_F1 ; 
 int /*<<< orphan*/  CTX_GLOBAL_BLOCK ; 
 int /*<<< orphan*/  CTX_MV_DATA ; 
 int /*<<< orphan*/  CTX_MV_F1 ; 
 int /*<<< orphan*/  CTX_PMODE_REF1 ; 
 int /*<<< orphan*/  CTX_PMODE_REF2 ; 
 int DIRAC_REF_MASK_GLOBAL ; 
 int DIRAC_REF_MASK_REF1 ; 
 int DIRAC_REF_MASK_REF2 ; 
 int dirac_get_arith_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dirac_get_arith_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_mv (TYPE_2__*,TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  pred_block_dc (TYPE_3__*,int,int,int) ; 
 int pred_block_mode (TYPE_3__*,int,int,int,int) ; 
 int /*<<< orphan*/  pred_mv (TYPE_3__*,int,int,int,int) ; 

__attribute__((used)) static void decode_block_params(DiracContext *s, DiracArith arith[8], DiracBlock *block,
                                int stride, int x, int y)
{
    int i;

    block->ref  = pred_block_mode(block, stride, x, y, DIRAC_REF_MASK_REF1);
    block->ref ^= dirac_get_arith_bit(arith, CTX_PMODE_REF1);

    if (s->num_refs == 2) {
        block->ref |= pred_block_mode(block, stride, x, y, DIRAC_REF_MASK_REF2);
        block->ref ^= dirac_get_arith_bit(arith, CTX_PMODE_REF2) << 1;
    }

    if (!block->ref) {
        pred_block_dc(block, stride, x, y);
        for (i = 0; i < 3; i++)
            block->u.dc[i] += (unsigned)dirac_get_arith_int(arith+1+i, CTX_DC_F1, CTX_DC_DATA);
        return;
    }

    if (s->globalmc_flag) {
        block->ref |= pred_block_mode(block, stride, x, y, DIRAC_REF_MASK_GLOBAL);
        block->ref ^= dirac_get_arith_bit(arith, CTX_GLOBAL_BLOCK) << 2;
    }

    for (i = 0; i < s->num_refs; i++)
        if (block->ref & (i+1)) {
            if (block->ref & DIRAC_REF_MASK_GLOBAL) {
                global_mv(s, block, x, y, i);
            } else {
                pred_mv(block, stride, x, y, i);
                block->u.mv[i][0] += (unsigned)dirac_get_arith_int(arith + 4 + 2 * i, CTX_MV_F1, CTX_MV_DATA);
                block->u.mv[i][1] += (unsigned)dirac_get_arith_int(arith + 5 + 2 * i, CTX_MV_F1, CTX_MV_DATA);
            }
        }
}