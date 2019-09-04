#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_25__ {int member_0; int member_1; int num; int den; } ;
struct TYPE_24__ {int level_idc; } ;
struct TYPE_18__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_17__ {scalar_t__ den; scalar_t__ num; } ;
struct TYPE_23__ {scalar_t__ video_format; scalar_t__ video_full_range_flag; scalar_t__ colour_primaries; scalar_t__ transfer_characteristics; scalar_t__ matrix_coefficients; scalar_t__ chroma_sample_loc_type; scalar_t__ fixed_frame_rate_flag; int crop_left; int crop_right; int crop_top; int crop_bottom; scalar_t__ level; TYPE_2__ tick_rate; TYPE_1__ sample_aspect_ratio; } ;
struct TYPE_20__ {int* bit_rate_value_minus1; int bit_rate_scale; } ;
struct TYPE_19__ {int* bit_rate_value_minus1; int bit_rate_scale; } ;
struct TYPE_21__ {int aspect_ratio_idc; int sar_width; int sar_height; int aspect_ratio_info_present_flag; scalar_t__ video_format; int video_signal_type_present_flag; scalar_t__ video_full_range_flag; scalar_t__ colour_primaries; int colour_description_present_flag; scalar_t__ transfer_characteristics; scalar_t__ matrix_coefficients; scalar_t__ chroma_sample_loc_type_top_field; scalar_t__ chroma_sample_loc_type_bottom_field; int chroma_loc_info_present_flag; int time_scale; int num_units_in_tick; int timing_info_present_flag; scalar_t__ fixed_frame_rate_flag; int max_dec_frame_buffering; scalar_t__ bitstream_restriction_flag; TYPE_4__ vcl_hrd_parameters; scalar_t__ vcl_hrd_parameters_present_flag; TYPE_3__ nal_hrd_parameters; scalar_t__ nal_hrd_parameters_present_flag; } ;
struct TYPE_22__ {int chroma_format_idc; int frame_mbs_only_flag; int frame_crop_left_offset; int frame_cropping_flag; int frame_crop_right_offset; int frame_crop_top_offset; int frame_crop_bottom_offset; int pic_width_in_mbs_minus1; int pic_height_in_map_units_minus1; int profile_idc; int level_idc; int constraint_set3_flag; int vui_parameters_present_flag; TYPE_5__ vui; scalar_t__ separate_colour_plane_flag; } ;
struct TYPE_16__ {TYPE_7__* priv_data; } ;
typedef  TYPE_6__ H264RawSPS ;
typedef  TYPE_7__ H264MetadataContext ;
typedef  TYPE_8__ H264LevelDescriptor ;
typedef  TYPE_9__ AVRational ;
typedef  TYPE_10__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  EINVAL ; 
 int FF_ARRAY_ELEMS (TYPE_9__ const*) ; 
 int H264_MAX_DPB_FRAMES ; 
 int INT64_C (int) ; 
 int INT_MAX ; 
 scalar_t__ LEVEL_AUTO ; 
 scalar_t__ LEVEL_UNSET ; 
 int UINT32_MAX ; 
 int /*<<< orphan*/  av_log (TYPE_10__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_reduce (int*,int*,scalar_t__,scalar_t__,int) ; 
 TYPE_8__* ff_h264_guess_level (int,int,int,int,int,int) ; 

__attribute__((used)) static int h264_metadata_update_sps(AVBSFContext *bsf,
                                    H264RawSPS *sps)
{
    H264MetadataContext *ctx = bsf->priv_data;
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

        sps->vui.time_scale        = num;
        sps->vui.num_units_in_tick = den;

        sps->vui.timing_info_present_flag = 1;
        need_vui = 1;
    }
    SET_OR_INFER(sps->vui.fixed_frame_rate_flag,
                 ctx->fixed_frame_rate_flag,
                 sps->vui.timing_info_present_flag, 0);

    if (sps->separate_colour_plane_flag || sps->chroma_format_idc == 0) {
        crop_unit_x = 1;
        crop_unit_y = 2 - sps->frame_mbs_only_flag;
    } else {
        crop_unit_x = 1 + (sps->chroma_format_idc < 3);
        crop_unit_y = (1 + (sps->chroma_format_idc < 2)) *
                       (2 - sps->frame_mbs_only_flag);
    }
#define CROP(border, unit) do { \
        if (ctx->crop_ ## border >= 0) { \
            if (ctx->crop_ ## border % unit != 0) { \
                av_log(bsf, AV_LOG_ERROR, "Invalid value for crop_%s: " \
                       "must be a multiple of %d.\n", #border, unit); \
                return AVERROR(EINVAL); \
            } \
            sps->frame_crop_ ## border ## _offset = \
                  ctx->crop_ ## border / unit; \
            sps->frame_cropping_flag = 1; \
        } \
    } while (0)
    CROP(left,   crop_unit_x);
    CROP(right,  crop_unit_x);
    CROP(top,    crop_unit_y);
    CROP(bottom, crop_unit_y);
#undef CROP

    if (ctx->level != LEVEL_UNSET) {
        int level_idc;

        if (ctx->level == LEVEL_AUTO) {
            const H264LevelDescriptor *desc;
            int64_t bit_rate;
            int width, height, dpb_frames;
            int framerate;

            if (sps->vui.nal_hrd_parameters_present_flag) {
                bit_rate = (sps->vui.nal_hrd_parameters.bit_rate_value_minus1[0] + 1) *
                    (INT64_C(1) << (sps->vui.nal_hrd_parameters.bit_rate_scale + 6));
            } else if (sps->vui.vcl_hrd_parameters_present_flag) {
                bit_rate = (sps->vui.vcl_hrd_parameters.bit_rate_value_minus1[0] + 1) *
                    (INT64_C(1) << (sps->vui.vcl_hrd_parameters.bit_rate_scale + 6));
                // Adjust for VCL vs. NAL limits.
                bit_rate = bit_rate * 6 / 5;
            } else {
                bit_rate = 0;
            }

            // Don't use max_dec_frame_buffering if it is only inferred.
            dpb_frames = sps->vui.bitstream_restriction_flag ?
                sps->vui.max_dec_frame_buffering : H264_MAX_DPB_FRAMES;

            width  = 16 * (sps->pic_width_in_mbs_minus1 + 1);
            height = 16 * (sps->pic_height_in_map_units_minus1 + 1) *
                (2 - sps->frame_mbs_only_flag);

            if (sps->vui.timing_info_present_flag)
                framerate = sps->vui.time_scale / sps->vui.num_units_in_tick / 2;
            else
                framerate = 0;

            desc = ff_h264_guess_level(sps->profile_idc, bit_rate, framerate,
                                       width, height, dpb_frames);
            if (desc) {
                level_idc = desc->level_idc;
            } else {
                av_log(bsf, AV_LOG_WARNING, "Stream does not appear to "
                       "conform to any level: using level 6.2.\n");
                level_idc = 62;
            }
        } else {
            level_idc = ctx->level;
        }

        if (level_idc == 9) {
            if (sps->profile_idc == 66 ||
                sps->profile_idc == 77 ||
                sps->profile_idc == 88) {
                sps->level_idc = 11;
                sps->constraint_set3_flag = 1;
            } else {
                sps->level_idc = 9;
            }
        } else {
            sps->level_idc = level_idc;
        }
    }

    if (need_vui)
        sps->vui_parameters_present_flag = 1;

    return 0;
}