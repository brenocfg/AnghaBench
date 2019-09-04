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
typedef  scalar_t__ uint64_t ;
typedef  int int32_t ;
typedef  enum MLPChMode { ____Placeholder_MLPChMode } MLPChMode ;
struct TYPE_3__ {int* sample_buffer; int number_of_samples; int num_channels; } ;
typedef  TYPE_1__ MLPEncodeContext ;

/* Variables and functions */
 scalar_t__ FFABS (int) ; 
 size_t MLP_CHMODE_LEFT_RIGHT ; 
 size_t MLP_CHMODE_LEFT_SIDE ; 
 size_t MLP_CHMODE_MID_SIDE ; 
 size_t MLP_CHMODE_RIGHT_SIDE ; 

__attribute__((used)) static enum MLPChMode estimate_stereo_mode(MLPEncodeContext *ctx)
{
    uint64_t score[4], sum[4] = { 0, 0, 0, 0, };
    int32_t *right_ch = ctx->sample_buffer + 1;
    int32_t *left_ch  = ctx->sample_buffer;
    int i;
    enum MLPChMode best = 0;

    for(i = 2; i < ctx->number_of_samples; i++) {
        int32_t left  = left_ch [i * ctx->num_channels] - 2 * left_ch [(i - 1) * ctx->num_channels] + left_ch [(i - 2) * ctx->num_channels];
        int32_t right = right_ch[i * ctx->num_channels] - 2 * right_ch[(i - 1) * ctx->num_channels] + right_ch[(i - 2) * ctx->num_channels];

        sum[0] += FFABS( left        );
        sum[1] += FFABS(        right);
        sum[2] += FFABS((left + right) >> 1);
        sum[3] += FFABS( left - right);
    }

    score[MLP_CHMODE_LEFT_RIGHT] = sum[0] + sum[1];
    score[MLP_CHMODE_LEFT_SIDE]  = sum[0] + sum[3];
    score[MLP_CHMODE_RIGHT_SIDE] = sum[1] + sum[3];
    score[MLP_CHMODE_MID_SIDE]   = sum[2] + sum[3];

    for(i = 1; i < 3; i++)
        if(score[i] < score[best])
            best = i;

    return best;
}