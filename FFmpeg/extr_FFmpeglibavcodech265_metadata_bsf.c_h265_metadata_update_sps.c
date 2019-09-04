#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_5__* priv_data; } ;
struct TYPE_17__ {int member_0; int member_1; int num; int den; } ;
struct TYPE_12__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_13__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_16__ {scalar_t__ video_format; scalar_t__ video_full_range_flag; scalar_t__ colour_primaries; scalar_t__ transfer_characteristics; scalar_t__ matrix_coefficients; scalar_t__ chroma_sample_loc_type; scalar_t__ num_ticks_poc_diff_one; int crop_left; int crop_right; int crop_top; int crop_bottom; TYPE_1__ tick_rate; TYPE_2__ sample_aspect_ratio; } ;
struct TYPE_14__ {int aspect_ratio_idc; int sar_width; int sar_height; int aspect_ratio_info_present_flag; scalar_t__ video_format; int video_signal_type_present_flag; scalar_t__ video_full_range_flag; scalar_t__ colour_primaries; int colour_description_present_flag; scalar_t__ transfer_characteristics; scalar_t__ matrix_coefficients; scalar_t__ chroma_sample_loc_type_top_field; scalar_t__ chroma_sample_loc_type_bottom_field; int chroma_loc_info_present_flag; int vui_time_scale; int vui_num_units_in_tick; int vui_timing_info_present_flag; scalar_t__ vui_num_ticks_poc_diff_one_minus1; int vui_poc_proportional_to_timing_flag; } ;
struct TYPE_15__ {int chroma_format_idc; int conf_win_left_offset; int conformance_window_flag; int conf_win_right_offset; int conf_win_top_offset; int conf_win_bottom_offset; int vui_parameters_present_flag; scalar_t__ separate_colour_plane_flag; TYPE_3__ vui; } ;
typedef  TYPE_4__ H265RawSPS ;
typedef  TYPE_5__ H265MetadataContext ;
typedef  TYPE_6__ AVRational ;
typedef  TYPE_7__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_ARRAY_ELEMS (TYPE_6__ const*) ; 
 int INT_MAX ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  av_reduce (int*,int*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int h265_metadata_update_sps(AVBSFContext *bsf,
                                    H265RawSPS *sps)
{
    H265MetadataContext *ctx = bsf->priv_data;
    int need_vui = 0;
    int crop_unit_x, crop_unit_y;

    if (ctx->sample_aspect_ratio.num && ctx->sample_aspect_ratio.den) {
        // Table E-1.
        static const AVRational sar_idc[] = {
            {   0,  0 }, // Unspecified (never written here).
            {   1,  1 }, {  12, 11 }, {  10, 11 }, {  16, 11 },
            {  40, 33 }, {  24, 11 }, {  20, 11 }, {  32, 11 },
            {  80, 33 }, {  18, 11 }, {  15, 11 }, {  64, 33 },
            { 160, 99 }, {   4,  3 }, {   3,  2 }, {   2,  1 },
        };
        int num, den, i;

        av_reduce(&num, &den, ctx->sample_aspect_ratio.num,
                  ctx->sample_aspect_ratio.den, 65535);

        for (i = 1; i < FF_ARRAY_ELEMS(sar_idc); i++) {
            if (num == sar_idc[i].num &&
                den == sar_idc[i].den)
                break;
        }
        if (i == FF_ARRAY_ELEMS(sar_idc)) {
            sps->vui.aspect_ratio_idc = 255;
            sps->vui.sar_width  = num;
            sps->vui.sar_height = den;
        } else {
            sps->vui.aspect_ratio_idc = i;
        }
        sps->vui.aspect_ratio_info_present_flag = 1;
        need_vui = 1;
    }

#define SET_OR_INFER(field, value, present_flag, infer) do { \
        if (value >= 0) { \
            field = value; \
            need_vui = 1; \
        } else if (!present_flag) \
            field = infer; \
    } while (0)

    if (ctx->video_format             >= 0 ||
        ctx->video_full_range_flag    >= 0 ||
        ctx->colour_primaries         >= 0 ||
        ctx->transfer_characteristics >= 0 ||
        ctx->matrix_coefficients      >= 0) {

        SET_OR_INFER(sps->vui.video_format, ctx->video_format,
                     sps->vui.video_signal_type_present_flag, 5);

        SET_OR_INFER(sps->vui.video_full_range_flag,
                     ctx->video_full_range_flag,
                     sps->vui.video_signal_type_present_flag, 0);

        if (ctx->colour_primaries         >= 0 ||
            ctx->transfer_characteristics >= 0 ||
            ctx->matrix_coefficients      >= 0) {

            SET_OR_INFER(sps->vui.colour_primaries,
                         ctx->colour_primaries,
                         sps->vui.colour_description_present_flag, 2);

            SET_OR_INFER(sps->vui.transfer_characteristics,
                         ctx->transfer_characteristics,
                         sps->vui.colour_description_present_flag, 2);

            SET_OR_INFER(sps->vui.matrix_coefficients,
                         ctx->matrix_coefficients,
                         sps->vui.colour_description_present_flag, 2);

            sps->vui.colour_description_present_flag = 1;
        }
        sps->vui.video_signal_type_present_flag = 1;
        need_vui = 1;
    }

    if (ctx->chroma_sample_loc_type >= 0) {
        sps->vui.chroma_sample_loc_type_top_field =
            ctx->chroma_sample_loc_type;
        sps->vui.chroma_sample_loc_type_bottom_field =
            ctx->chroma_sample_loc_type;
        sps->vui.chroma_loc_info_present_flag = 1;
        need_vui = 1;
    }

    if (ctx->tick_rate.num && ctx->tick_rate.den) {
        int num, den;

        av_reduce(&num, &den, ctx->tick_rate.num, ctx->tick_rate.den,
                  UINT32_MAX > INT_MAX ? UINT32_MAX : INT_MAX);

        sps->vui.vui_time_scale        = num;
        sps->vui.vui_num_units_in_tick = den;

        sps->vui.vui_timing_info_present_flag = 1;
        need_vui = 1;

        if (ctx->num_ticks_poc_diff_one > 0) {
            sps->vui.vui_num_ticks_poc_diff_one_minus1 =
                ctx->num_ticks_poc_diff_one - 1;
            sps->vui.vui_poc_proportional_to_timing_flag = 1;
        } else if (ctx->num_ticks_poc_diff_one == 0) {
            sps->vui.vui_poc_proportional_to_timing_flag = 0;
        }
    }

    if (sps->separate_colour_plane_flag || sps->chroma_format_idc == 0) {
        crop_unit_x = 1;
        crop_unit_y = 1;
    } else {
        crop_unit_x = 1 + (sps->chroma_format_idc < 3);
        crop_unit_y = 1 + (sps->chroma_format_idc < 2);
    }
#define CROP(border, unit) do { \
        if (ctx->crop_ ## border >= 0) { \
            if (ctx->crop_ ## border % unit != 0) { \
                av_log(bsf, AV_LOG_ERROR, "Invalid value for crop_%s: " \
                       "must be a multiple of %d.\n", #border, unit); \
                return AVERROR(EINVAL); \
            } \
            sps->conf_win_ ## border ## _offset = \
                ctx->crop_ ## border / unit; \
            sps->conformance_window_flag = 1; \
        } \
    } while (0)
    CROP(left,   crop_unit_x);
    CROP(right,  crop_unit_x);
    CROP(top,    crop_unit_y);
    CROP(bottom, crop_unit_y);
#undef CROP

    if (need_vui)
        sps->vui_parameters_present_flag = 1;

    return 0;
}