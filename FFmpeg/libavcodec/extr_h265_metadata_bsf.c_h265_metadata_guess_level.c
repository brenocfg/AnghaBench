#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_12__ ;
typedef  struct TYPE_18__   TYPE_11__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_26__ {int /*<<< orphan*/  level_idc; int /*<<< orphan*/  name; } ;
struct TYPE_25__ {int /*<<< orphan*/  level_guess; } ;
struct TYPE_24__ {int bit_rate_scale; TYPE_3__* vcl_sub_layer_hrd_parameters; scalar_t__ vcl_hrd_parameters_present_flag; TYPE_2__* nal_sub_layer_hrd_parameters; scalar_t__ nal_hrd_parameters_present_flag; } ;
struct TYPE_20__ {TYPE_7__ hrd_parameters; scalar_t__ vui_hrd_parameters_present_flag; } ;
struct TYPE_23__ {int* vps_max_dec_pic_buffering_minus1; scalar_t__ vps_num_hrd_parameters; int* sps_max_dec_pic_buffering_minus1; int pic_width_in_luma_samples; int pic_height_in_luma_samples; int num_tile_columns_minus1; int num_tile_rows_minus1; scalar_t__ tiles_enabled_flag; TYPE_1__ vui; int /*<<< orphan*/  profile_tier_level; TYPE_7__* hrd_parameters; } ;
struct TYPE_22__ {int* bit_rate_value_minus1; } ;
struct TYPE_21__ {int* bit_rate_value_minus1; } ;
struct TYPE_19__ {TYPE_8__* priv_data; } ;
struct TYPE_18__ {int nb_units; TYPE_10__* units; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_4__* content; } ;
typedef  TYPE_4__ H265RawVPS ;
typedef  TYPE_4__ H265RawSPS ;
typedef  int /*<<< orphan*/  H265RawProfileTierLevel ;
typedef  TYPE_4__ H265RawPPS ;
typedef  TYPE_7__ H265RawHRDParameters ;
typedef  TYPE_8__ H265MetadataContext ;
typedef  TYPE_9__ H265LevelDescriptor ;
typedef  TYPE_10__ CodedBitstreamUnit ;
typedef  TYPE_11__ CodedBitstreamFragment ;
typedef  TYPE_12__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 scalar_t__ HEVC_NAL_PPS ; 
 scalar_t__ HEVC_NAL_SPS ; 
 scalar_t__ HEVC_NAL_VPS ; 
 int INT64_C (int) ; 
 int /*<<< orphan*/  av_log (TYPE_12__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_9__* ff_h265_guess_level (int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void h265_metadata_guess_level(AVBSFContext *bsf,
                                      const CodedBitstreamFragment *au)
{
    H265MetadataContext *ctx = bsf->priv_data;
    const H265LevelDescriptor *desc;
    const H265RawProfileTierLevel *ptl = NULL;
    const H265RawHRDParameters    *hrd = NULL;
    int64_t bit_rate = 0;
    int width = 0, height = 0;
    int tile_cols = 0, tile_rows = 0;
    int max_dec_pic_buffering = 0;
    int i;

    for (i = 0; i < au->nb_units; i++) {
        const CodedBitstreamUnit *unit = &au->units[i];

        if (unit->type == HEVC_NAL_VPS) {
            const H265RawVPS *vps = unit->content;

            ptl = &vps->profile_tier_level;
            max_dec_pic_buffering = vps->vps_max_dec_pic_buffering_minus1[0] + 1;

            if (vps->vps_num_hrd_parameters > 0)
                hrd = &vps->hrd_parameters[0];

        } else if (unit->type == HEVC_NAL_SPS) {
            const H265RawSPS *sps = unit->content;

            ptl = &sps->profile_tier_level;
            max_dec_pic_buffering = sps->sps_max_dec_pic_buffering_minus1[0] + 1;

            width  = sps->pic_width_in_luma_samples;
            height = sps->pic_height_in_luma_samples;

            if (sps->vui.vui_hrd_parameters_present_flag)
                hrd = &sps->vui.hrd_parameters;

        } else if (unit->type == HEVC_NAL_PPS) {
            const H265RawPPS *pps = unit->content;

            if (pps->tiles_enabled_flag) {
                tile_cols = pps->num_tile_columns_minus1 + 1;
                tile_rows = pps->num_tile_rows_minus1 + 1;
            }
        }
    }

    if (hrd) {
        if (hrd->nal_hrd_parameters_present_flag) {
            bit_rate = (hrd->nal_sub_layer_hrd_parameters[0].bit_rate_value_minus1[0] + 1) *
                       (INT64_C(1) << hrd->bit_rate_scale + 6);
        } else if (hrd->vcl_hrd_parameters_present_flag) {
            bit_rate = (hrd->vcl_sub_layer_hrd_parameters[0].bit_rate_value_minus1[0] + 1) *
                       (INT64_C(1) << hrd->bit_rate_scale + 6);
            // Adjust for VCL vs. NAL limits.
            bit_rate = bit_rate * 11 / 10;
        }
    }

    desc = ff_h265_guess_level(ptl, bit_rate, width, height,
                               0, tile_cols, tile_rows,
                               max_dec_pic_buffering);
    if (desc) {
        av_log(bsf, AV_LOG_DEBUG, "Stream appears to conform to "
               "level %s.\n", desc->name);
        ctx->level_guess = desc->level_idc;
    }
}