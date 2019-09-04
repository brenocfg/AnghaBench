#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* slice_ctx; } ;
struct TYPE_5__ {unsigned char* luma_weight_flag; unsigned char* chroma_weight_flag; short*** luma_weight; int luma_log2_weight_denom; short**** chroma_weight; int chroma_log2_weight_denom; } ;
struct TYPE_6__ {unsigned int* ref_count; TYPE_1__ pwt; } ;
typedef  TYPE_2__ H264SliceContext ;
typedef  TYPE_3__ H264Context ;

/* Variables and functions */

__attribute__((used)) static void fill_vaapi_plain_pred_weight_table(const H264Context *h,
                                               int            list,
                                               unsigned char *luma_weight_flag,
                                               short          luma_weight[32],
                                               short          luma_offset[32],
                                               unsigned char *chroma_weight_flag,
                                               short          chroma_weight[32][2],
                                               short          chroma_offset[32][2])
{
    const H264SliceContext *sl = &h->slice_ctx[0];
    unsigned int i, j;

    *luma_weight_flag    = sl->pwt.luma_weight_flag[list];
    *chroma_weight_flag  = sl->pwt.chroma_weight_flag[list];

    for (i = 0; i < sl->ref_count[list]; i++) {
        /* VA API also wants the inferred (default) values, not
           only what is available in the bitstream (7.4.3.2). */
        if (sl->pwt.luma_weight_flag[list]) {
            luma_weight[i] = sl->pwt.luma_weight[i][list][0];
            luma_offset[i] = sl->pwt.luma_weight[i][list][1];
        } else {
            luma_weight[i] = 1 << sl->pwt.luma_log2_weight_denom;
            luma_offset[i] = 0;
        }
        for (j = 0; j < 2; j++) {
            if (sl->pwt.chroma_weight_flag[list]) {
                chroma_weight[i][j] = sl->pwt.chroma_weight[i][list][j][0];
                chroma_offset[i][j] = sl->pwt.chroma_weight[i][list][j][1];
            } else {
                chroma_weight[i][j] = 1 << sl->pwt.chroma_log2_weight_denom;
                chroma_offset[i][j] = 0;
            }
        }
    }
}