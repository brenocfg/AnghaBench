#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/ * ScalingListDCCoeff32x32; int /*<<< orphan*/ * ScalingListDCCoeff16x16; int /*<<< orphan*/ ** ScalingList32x32; int /*<<< orphan*/ ** ScalingList16x16; int /*<<< orphan*/ ** ScalingList8x8; int /*<<< orphan*/ ** ScalingList4x4; } ;
struct TYPE_11__ {TYPE_2__* sps; TYPE_1__* pps; } ;
struct TYPE_13__ {TYPE_3__ ps; } ;
struct TYPE_12__ {int /*<<< orphan*/ ** sl_dc; int /*<<< orphan*/ *** sl; } ;
struct TYPE_10__ {TYPE_4__ scaling_list; } ;
struct TYPE_9__ {TYPE_4__ scaling_list; scalar_t__ scaling_list_data_present_flag; } ;
typedef  TYPE_4__ ScalingList ;
typedef  TYPE_5__ HEVCContext ;
typedef  TYPE_6__ CUVIDHEVCPICPARAMS ;

/* Variables and functions */
 int* ff_hevc_diag_scan4x4_x ; 
 int* ff_hevc_diag_scan4x4_y ; 
 int* ff_hevc_diag_scan8x8_x ; 
 int* ff_hevc_diag_scan8x8_y ; 

__attribute__((used)) static void fill_scaling_lists(CUVIDHEVCPICPARAMS *ppc, const HEVCContext *s)
{
    const ScalingList *sl = s->ps.pps->scaling_list_data_present_flag ?
                            &s->ps.pps->scaling_list : &s->ps.sps->scaling_list;
    int i, j, pos;

    for (i = 0; i < 6; i++) {
        for (j = 0; j < 16; j++) {
            pos = 4 * ff_hevc_diag_scan4x4_y[j] + ff_hevc_diag_scan4x4_x[j];
            ppc->ScalingList4x4[i][j] = sl->sl[0][i][pos];
        }

        for (j = 0; j < 64; j++) {
            pos = 8 * ff_hevc_diag_scan8x8_y[j] + ff_hevc_diag_scan8x8_x[j];
            ppc->ScalingList8x8[i][j]   = sl->sl[1][i][pos];
            ppc->ScalingList16x16[i][j] = sl->sl[2][i][pos];

            if (i < 2)
                ppc->ScalingList32x32[i][j] = sl->sl[3][i * 3][pos];
        }

        ppc->ScalingListDCCoeff16x16[i] = sl->sl_dc[0][i];
        if (i < 2)
            ppc->ScalingListDCCoeff32x32[i] = sl->sl_dc[1][i * 3];
    }
}