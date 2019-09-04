#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pred_angular; int /*<<< orphan*/  pred_dc; int /*<<< orphan*/ * pred_planar; int /*<<< orphan*/ * intra_pred; } ;
typedef  TYPE_1__ HEVCPredContext ;

/* Variables and functions */
 scalar_t__ ARCH_MIPS ; 
 int /*<<< orphan*/  ff_hevc_pred_init_mips (TYPE_1__*,int) ; 
 int /*<<< orphan*/  intra_pred_2_10 ; 
 int /*<<< orphan*/  intra_pred_2_12 ; 
 int /*<<< orphan*/  intra_pred_2_8 ; 
 int /*<<< orphan*/  intra_pred_2_9 ; 
 int /*<<< orphan*/  intra_pred_3_10 ; 
 int /*<<< orphan*/  intra_pred_3_12 ; 
 int /*<<< orphan*/  intra_pred_3_8 ; 
 int /*<<< orphan*/  intra_pred_3_9 ; 
 int /*<<< orphan*/  intra_pred_4_10 ; 
 int /*<<< orphan*/  intra_pred_4_12 ; 
 int /*<<< orphan*/  intra_pred_4_8 ; 
 int /*<<< orphan*/  intra_pred_4_9 ; 
 int /*<<< orphan*/  intra_pred_5_10 ; 
 int /*<<< orphan*/  intra_pred_5_12 ; 
 int /*<<< orphan*/  intra_pred_5_8 ; 
 int /*<<< orphan*/  intra_pred_5_9 ; 
 int /*<<< orphan*/  pred_angular_0_10 ; 
 int /*<<< orphan*/  pred_angular_0_12 ; 
 int /*<<< orphan*/  pred_angular_0_8 ; 
 int /*<<< orphan*/  pred_angular_0_9 ; 
 int /*<<< orphan*/  pred_angular_1_10 ; 
 int /*<<< orphan*/  pred_angular_1_12 ; 
 int /*<<< orphan*/  pred_angular_1_8 ; 
 int /*<<< orphan*/  pred_angular_1_9 ; 
 int /*<<< orphan*/  pred_angular_2_10 ; 
 int /*<<< orphan*/  pred_angular_2_12 ; 
 int /*<<< orphan*/  pred_angular_2_8 ; 
 int /*<<< orphan*/  pred_angular_2_9 ; 
 int /*<<< orphan*/  pred_angular_3_10 ; 
 int /*<<< orphan*/  pred_angular_3_12 ; 
 int /*<<< orphan*/  pred_angular_3_8 ; 
 int /*<<< orphan*/  pred_angular_3_9 ; 
 int /*<<< orphan*/  pred_dc_10 ; 
 int /*<<< orphan*/  pred_dc_12 ; 
 int /*<<< orphan*/  pred_dc_8 ; 
 int /*<<< orphan*/  pred_dc_9 ; 
 int /*<<< orphan*/  pred_planar_0_10 ; 
 int /*<<< orphan*/  pred_planar_0_12 ; 
 int /*<<< orphan*/  pred_planar_0_8 ; 
 int /*<<< orphan*/  pred_planar_0_9 ; 
 int /*<<< orphan*/  pred_planar_1_10 ; 
 int /*<<< orphan*/  pred_planar_1_12 ; 
 int /*<<< orphan*/  pred_planar_1_8 ; 
 int /*<<< orphan*/  pred_planar_1_9 ; 
 int /*<<< orphan*/  pred_planar_2_10 ; 
 int /*<<< orphan*/  pred_planar_2_12 ; 
 int /*<<< orphan*/  pred_planar_2_8 ; 
 int /*<<< orphan*/  pred_planar_2_9 ; 
 int /*<<< orphan*/  pred_planar_3_10 ; 
 int /*<<< orphan*/  pred_planar_3_12 ; 
 int /*<<< orphan*/  pred_planar_3_8 ; 
 int /*<<< orphan*/  pred_planar_3_9 ; 

void ff_hevc_pred_init(HEVCPredContext *hpc, int bit_depth)
{
#undef FUNC
#define FUNC(a, depth) a ## _ ## depth

#define HEVC_PRED(depth)                                \
    hpc->intra_pred[0]   = FUNC(intra_pred_2, depth);   \
    hpc->intra_pred[1]   = FUNC(intra_pred_3, depth);   \
    hpc->intra_pred[2]   = FUNC(intra_pred_4, depth);   \
    hpc->intra_pred[3]   = FUNC(intra_pred_5, depth);   \
    hpc->pred_planar[0]  = FUNC(pred_planar_0, depth);  \
    hpc->pred_planar[1]  = FUNC(pred_planar_1, depth);  \
    hpc->pred_planar[2]  = FUNC(pred_planar_2, depth);  \
    hpc->pred_planar[3]  = FUNC(pred_planar_3, depth);  \
    hpc->pred_dc         = FUNC(pred_dc, depth);        \
    hpc->pred_angular[0] = FUNC(pred_angular_0, depth); \
    hpc->pred_angular[1] = FUNC(pred_angular_1, depth); \
    hpc->pred_angular[2] = FUNC(pred_angular_2, depth); \
    hpc->pred_angular[3] = FUNC(pred_angular_3, depth);

    switch (bit_depth) {
    case 9:
        HEVC_PRED(9);
        break;
    case 10:
        HEVC_PRED(10);
        break;
    case 12:
        HEVC_PRED(12);
        break;
    default:
        HEVC_PRED(8);
        break;
    }

    if (ARCH_MIPS)
        ff_hevc_pred_init_mips(hpc, bit_depth);
}