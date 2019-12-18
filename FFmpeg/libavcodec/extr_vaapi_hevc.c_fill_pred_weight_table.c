#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int delta_chroma_log2_weight_denom; int luma_log2_weight_denom; scalar_t__** ChromaOffsetL1; scalar_t__** delta_chroma_weight_l1; scalar_t__** luma_offset_l1; scalar_t__** delta_luma_weight_l1; scalar_t__** ChromaOffsetL0; scalar_t__** delta_chroma_weight_l0; scalar_t__** luma_offset_l0; scalar_t__** delta_luma_weight_l0; } ;
typedef  TYPE_4__ VASliceParameterBufferHEVC ;
struct TYPE_12__ {TYPE_2__* sps; TYPE_1__* pps; } ;
struct TYPE_15__ {TYPE_3__ ps; } ;
struct TYPE_14__ {scalar_t__ slice_type; int luma_log2_weight_denom; int chroma_log2_weight_denom; int* nb_refs; scalar_t__** chroma_offset_l1; scalar_t__** chroma_weight_l1; scalar_t__** luma_offset_l1; scalar_t__** luma_weight_l1; scalar_t__** chroma_offset_l0; scalar_t__** chroma_weight_l0; scalar_t__** luma_offset_l0; scalar_t__** luma_weight_l0; } ;
struct TYPE_11__ {scalar_t__ chroma_format_idc; } ;
struct TYPE_10__ {int /*<<< orphan*/  weighted_bipred_flag; int /*<<< orphan*/  weighted_pred_flag; } ;
typedef  TYPE_5__ SliceHeader ;
typedef  TYPE_6__ HEVCContext ;

/* Variables and functions */
 scalar_t__ HEVC_SLICE_B ; 
 scalar_t__ HEVC_SLICE_I ; 
 scalar_t__ HEVC_SLICE_P ; 
 size_t L0 ; 
 size_t L1 ; 
 int /*<<< orphan*/  memset (scalar_t__**,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fill_pred_weight_table(const HEVCContext *h,
                                   const SliceHeader *sh,
                                   VASliceParameterBufferHEVC *slice_param)
{
    int i;

    memset(slice_param->delta_luma_weight_l0,   0, sizeof(slice_param->delta_luma_weight_l0));
    memset(slice_param->delta_luma_weight_l1,   0, sizeof(slice_param->delta_luma_weight_l1));
    memset(slice_param->luma_offset_l0,         0, sizeof(slice_param->luma_offset_l0));
    memset(slice_param->luma_offset_l1,         0, sizeof(slice_param->luma_offset_l1));
    memset(slice_param->delta_chroma_weight_l0, 0, sizeof(slice_param->delta_chroma_weight_l0));
    memset(slice_param->delta_chroma_weight_l1, 0, sizeof(slice_param->delta_chroma_weight_l1));
    memset(slice_param->ChromaOffsetL0,         0, sizeof(slice_param->ChromaOffsetL0));
    memset(slice_param->ChromaOffsetL1,         0, sizeof(slice_param->ChromaOffsetL1));

    slice_param->delta_chroma_log2_weight_denom = 0;
    slice_param->luma_log2_weight_denom         = 0;

    if (sh->slice_type == HEVC_SLICE_I ||
        (sh->slice_type == HEVC_SLICE_P && !h->ps.pps->weighted_pred_flag) ||
        (sh->slice_type == HEVC_SLICE_B && !h->ps.pps->weighted_bipred_flag))
        return;

    slice_param->luma_log2_weight_denom = sh->luma_log2_weight_denom;

    if (h->ps.sps->chroma_format_idc) {
        slice_param->delta_chroma_log2_weight_denom = sh->chroma_log2_weight_denom - sh->luma_log2_weight_denom;
    }

    for (i = 0; i < 15 && i < sh->nb_refs[L0]; i++) {
        slice_param->delta_luma_weight_l0[i] = sh->luma_weight_l0[i] - (1 << sh->luma_log2_weight_denom);
        slice_param->luma_offset_l0[i] = sh->luma_offset_l0[i];
        slice_param->delta_chroma_weight_l0[i][0] = sh->chroma_weight_l0[i][0] - (1 << sh->chroma_log2_weight_denom);
        slice_param->delta_chroma_weight_l0[i][1] = sh->chroma_weight_l0[i][1] - (1 << sh->chroma_log2_weight_denom);
        slice_param->ChromaOffsetL0[i][0] = sh->chroma_offset_l0[i][0];
        slice_param->ChromaOffsetL0[i][1] = sh->chroma_offset_l0[i][1];
    }

    if (sh->slice_type == HEVC_SLICE_B) {
        for (i = 0; i < 15 && i < sh->nb_refs[L1]; i++) {
            slice_param->delta_luma_weight_l1[i] = sh->luma_weight_l1[i] - (1 << sh->luma_log2_weight_denom);
            slice_param->luma_offset_l1[i] = sh->luma_offset_l1[i];
            slice_param->delta_chroma_weight_l1[i][0] = sh->chroma_weight_l1[i][0] - (1 << sh->chroma_log2_weight_denom);
            slice_param->delta_chroma_weight_l1[i][1] = sh->chroma_weight_l1[i][1] - (1 << sh->chroma_log2_weight_denom);
            slice_param->ChromaOffsetL1[i][0] = sh->chroma_offset_l1[i][0];
            slice_param->ChromaOffsetL1[i][1] = sh->chroma_offset_l1[i][1];
        }
    }
}