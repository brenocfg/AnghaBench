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
struct TYPE_10__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_15__ {scalar_t__ color_primaries; scalar_t__ transfer_characteristics; scalar_t__ matrix_coefficients; scalar_t__ color_range; scalar_t__ chroma_sample_position; scalar_t__ num_ticks_per_picture; TYPE_1__ tick_rate; } ;
struct TYPE_14__ {int color_description_present_flag; scalar_t__ color_primaries; scalar_t__ transfer_characteristics; scalar_t__ matrix_coefficients; scalar_t__ color_range; scalar_t__ chroma_sample_position; int /*<<< orphan*/  subsampling_y; int /*<<< orphan*/  subsampling_x; scalar_t__ mono_chrome; } ;
struct TYPE_12__ {int time_scale; int num_units_in_display_tick; int equal_picture_interval; scalar_t__ num_ticks_per_picture_minus_1; } ;
struct TYPE_13__ {int timing_info_present_flag; TYPE_3__ timing_info; TYPE_5__ color_config; } ;
struct TYPE_11__ {TYPE_6__* priv_data; } ;
typedef  TYPE_2__ AVBSFContext ;
typedef  TYPE_3__ AV1RawTimingInfo ;
typedef  TYPE_4__ AV1RawSequenceHeader ;
typedef  TYPE_5__ AV1RawColorConfig ;
typedef  TYPE_6__ AV1MetadataContext ;

/* Variables and functions */
 scalar_t__ AVCOL_PRI_BT709 ; 
 scalar_t__ AVCOL_SPC_RGB ; 
 scalar_t__ AVCOL_TRC_IEC61966_2_1 ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ UINT32_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_reduce (int*,int*,scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int av1_metadata_update_sequence_header(AVBSFContext *bsf,
                                               AV1RawSequenceHeader *seq)
{
    AV1MetadataContext *ctx = bsf->priv_data;
    AV1RawColorConfig  *clc = &seq->color_config;
    AV1RawTimingInfo   *tim = &seq->timing_info;

    if (ctx->color_primaries >= 0          ||
        ctx->transfer_characteristics >= 0 ||
        ctx->matrix_coefficients >= 0) {
        clc->color_description_present_flag = 1;

        if (ctx->color_primaries >= 0)
            clc->color_primaries = ctx->color_primaries;
        if (ctx->transfer_characteristics >= 0)
            clc->transfer_characteristics = ctx->transfer_characteristics;
        if (ctx->matrix_coefficients >= 0)
            clc->matrix_coefficients = ctx->matrix_coefficients;
    }

    if (ctx->color_range >= 0) {
        if (clc->color_primaries          == AVCOL_PRI_BT709        &&
            clc->transfer_characteristics == AVCOL_TRC_IEC61966_2_1 &&
            clc->matrix_coefficients      == AVCOL_SPC_RGB) {
            av_log(bsf, AV_LOG_WARNING, "Warning: color_range cannot be set "
                   "on RGB streams encoded in BT.709 sRGB.\n");
        } else {
            clc->color_range = ctx->color_range;
        }
    }

    if (ctx->chroma_sample_position >= 0) {
        if (clc->mono_chrome || !clc->subsampling_x || !clc->subsampling_y) {
            av_log(bsf, AV_LOG_WARNING, "Warning: chroma_sample_position "
                   "can only be set for 4:2:0 streams.\n");
        } else {
            clc->chroma_sample_position = ctx->chroma_sample_position;
        }
    }

    if (ctx->tick_rate.num && ctx->tick_rate.den) {
        int num, den;

        av_reduce(&num, &den, ctx->tick_rate.num, ctx->tick_rate.den,
                  UINT32_MAX > INT_MAX ? UINT32_MAX : INT_MAX);

        tim->time_scale                = num;
        tim->num_units_in_display_tick = den;
        seq->timing_info_present_flag  = 1;

        if (ctx->num_ticks_per_picture > 0) {
            tim->equal_picture_interval = 1;
            tim->num_ticks_per_picture_minus_1 =
                ctx->num_ticks_per_picture - 1;
        }
    }

    return 0;
}