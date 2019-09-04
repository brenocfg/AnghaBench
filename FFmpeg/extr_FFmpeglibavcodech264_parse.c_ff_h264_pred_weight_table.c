#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
struct TYPE_6__ {int use_weight; int use_weight_chroma; unsigned int luma_log2_weight_denom; unsigned int chroma_log2_weight_denom; int* luma_weight_flag; int* chroma_weight_flag; int*** luma_weight; int**** chroma_weight; } ;
struct TYPE_5__ {scalar_t__ chroma_format_idc; } ;
typedef  TYPE_1__ SPS ;
typedef  TYPE_2__ H264PredWeightTable ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PICTURE_TYPE_B ; 
 int PICT_FRAME ; 
 int /*<<< orphan*/  av_log (void*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  avpriv_request_sample (void*,char*) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 void* get_se_golomb (int /*<<< orphan*/ *) ; 
 void* get_ue_golomb (int /*<<< orphan*/ *) ; 

int ff_h264_pred_weight_table(GetBitContext *gb, const SPS *sps,
                              const int *ref_count, int slice_type_nos,
                              H264PredWeightTable *pwt,
                              int picture_structure, void *logctx)
{
    int list, i, j;
    int luma_def, chroma_def;

    pwt->use_weight             = 0;
    pwt->use_weight_chroma      = 0;

    pwt->luma_log2_weight_denom = get_ue_golomb(gb);
    if (pwt->luma_log2_weight_denom > 7U) {
        av_log(logctx, AV_LOG_ERROR, "luma_log2_weight_denom %d is out of range\n", pwt->luma_log2_weight_denom);
        pwt->luma_log2_weight_denom = 0;
    }
    luma_def = 1 << pwt->luma_log2_weight_denom;

    if (sps->chroma_format_idc) {
        pwt->chroma_log2_weight_denom = get_ue_golomb(gb);
        if (pwt->chroma_log2_weight_denom > 7U) {
            av_log(logctx, AV_LOG_ERROR, "chroma_log2_weight_denom %d is out of range\n", pwt->chroma_log2_weight_denom);
            pwt->chroma_log2_weight_denom = 0;
        }
        chroma_def = 1 << pwt->chroma_log2_weight_denom;
    }

    for (list = 0; list < 2; list++) {
        pwt->luma_weight_flag[list]   = 0;
        pwt->chroma_weight_flag[list] = 0;
        for (i = 0; i < ref_count[list]; i++) {
            int luma_weight_flag, chroma_weight_flag;

            luma_weight_flag = get_bits1(gb);
            if (luma_weight_flag) {
                pwt->luma_weight[i][list][0] = get_se_golomb(gb);
                pwt->luma_weight[i][list][1] = get_se_golomb(gb);
                if ((int8_t)pwt->luma_weight[i][list][0] != pwt->luma_weight[i][list][0] ||
                    (int8_t)pwt->luma_weight[i][list][1] != pwt->luma_weight[i][list][1])
                    goto out_range_weight;
                if (pwt->luma_weight[i][list][0] != luma_def ||
                    pwt->luma_weight[i][list][1] != 0) {
                    pwt->use_weight             = 1;
                    pwt->luma_weight_flag[list] = 1;
                }
            } else {
                pwt->luma_weight[i][list][0] = luma_def;
                pwt->luma_weight[i][list][1] = 0;
            }

            if (sps->chroma_format_idc) {
                chroma_weight_flag = get_bits1(gb);
                if (chroma_weight_flag) {
                    int j;
                    for (j = 0; j < 2; j++) {
                        pwt->chroma_weight[i][list][j][0] = get_se_golomb(gb);
                        pwt->chroma_weight[i][list][j][1] = get_se_golomb(gb);
                        if ((int8_t)pwt->chroma_weight[i][list][j][0] != pwt->chroma_weight[i][list][j][0] ||
                            (int8_t)pwt->chroma_weight[i][list][j][1] != pwt->chroma_weight[i][list][j][1]) {
                            pwt->chroma_weight[i][list][j][0] = chroma_def;
                            pwt->chroma_weight[i][list][j][1] = 0;
                            goto out_range_weight;
                        }
                        if (pwt->chroma_weight[i][list][j][0] != chroma_def ||
                            pwt->chroma_weight[i][list][j][1] != 0) {
                            pwt->use_weight_chroma        = 1;
                            pwt->chroma_weight_flag[list] = 1;
                        }
                    }
                } else {
                    int j;
                    for (j = 0; j < 2; j++) {
                        pwt->chroma_weight[i][list][j][0] = chroma_def;
                        pwt->chroma_weight[i][list][j][1] = 0;
                    }
                }
            }

            // for MBAFF
            if (picture_structure == PICT_FRAME) {
                pwt->luma_weight[16 + 2 * i][list][0] = pwt->luma_weight[16 + 2 * i + 1][list][0] = pwt->luma_weight[i][list][0];
                pwt->luma_weight[16 + 2 * i][list][1] = pwt->luma_weight[16 + 2 * i + 1][list][1] = pwt->luma_weight[i][list][1];
                if (sps->chroma_format_idc) {
                    for (j = 0; j < 2; j++) {
                        pwt->chroma_weight[16 + 2 * i][list][j][0] = pwt->chroma_weight[16 + 2 * i + 1][list][j][0] = pwt->chroma_weight[i][list][j][0];
                        pwt->chroma_weight[16 + 2 * i][list][j][1] = pwt->chroma_weight[16 + 2 * i + 1][list][j][1] = pwt->chroma_weight[i][list][j][1];
                    }
                }
            }
        }
        if (slice_type_nos != AV_PICTURE_TYPE_B)
            break;
    }
    pwt->use_weight = pwt->use_weight || pwt->use_weight_chroma;
    return 0;
out_range_weight:
    avpriv_request_sample(logctx, "Out of range weight");
    return AVERROR_INVALIDDATA;
}