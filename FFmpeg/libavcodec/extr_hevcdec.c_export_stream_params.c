#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {scalar_t__ bottom_offset; scalar_t__ top_offset; scalar_t__ right_offset; scalar_t__ left_offset; } ;
struct TYPE_29__ {scalar_t__ preferred_transfer_characteristics; scalar_t__ present; } ;
struct TYPE_30__ {TYPE_7__ alternative_transfer; } ;
struct TYPE_28__ {int /*<<< orphan*/  num; int /*<<< orphan*/  den; } ;
struct TYPE_27__ {scalar_t__ transfer_characteristic; unsigned int vui_num_units_in_tick; unsigned int vui_time_scale; scalar_t__ vui_timing_info_present_flag; int /*<<< orphan*/  matrix_coeffs; int /*<<< orphan*/  colour_primaries; scalar_t__ colour_description_present_flag; scalar_t__ video_full_range_flag; scalar_t__ video_signal_type_present_flag; int /*<<< orphan*/  sar; } ;
struct TYPE_25__ {int /*<<< orphan*/  level_idc; int /*<<< orphan*/  profile_idc; } ;
struct TYPE_26__ {TYPE_3__ general_ptl; } ;
struct TYPE_24__ {int /*<<< orphan*/  num_reorder_pics; } ;
struct TYPE_23__ {scalar_t__ data; } ;
struct TYPE_22__ {scalar_t__ color_trc; TYPE_6__ framerate; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  color_primaries; void* color_range; int /*<<< orphan*/  level; int /*<<< orphan*/  profile; int /*<<< orphan*/  has_b_frames; scalar_t__ height; scalar_t__ width; scalar_t__ coded_height; scalar_t__ coded_width; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_20__ {TYPE_1__** vps_list; } ;
struct TYPE_21__ {TYPE_8__ sei; TYPE_12__ ps; TYPE_14__* avctx; } ;
struct TYPE_19__ {size_t vps_id; int max_sub_layers; TYPE_5__ vui; TYPE_4__ ptl; TYPE_2__* temporal_layer; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  pix_fmt; TYPE_9__ output_window; } ;
struct TYPE_18__ {unsigned int vps_num_units_in_tick; unsigned int vps_time_scale; scalar_t__ vps_timing_info_present_flag; } ;
typedef  TYPE_9__ HEVCWindow ;
typedef  TYPE_10__ HEVCVPS ;
typedef  TYPE_11__ HEVCSPS ;
typedef  TYPE_12__ HEVCParamSets ;
typedef  TYPE_13__ HEVCContext ;
typedef  TYPE_14__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVCOL_PRI_UNSPECIFIED ; 
 void* AVCOL_RANGE_JPEG ; 
 void* AVCOL_RANGE_MPEG ; 
 int /*<<< orphan*/  AVCOL_SPC_UNSPECIFIED ; 
 scalar_t__ AVCOL_TRC_UNSPECIFIED ; 
 scalar_t__ av_color_transfer_name (scalar_t__) ; 
 int /*<<< orphan*/  av_reduce (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  ff_set_sar (TYPE_14__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void export_stream_params(HEVCContext *s, const HEVCSPS *sps)
{
    AVCodecContext *avctx = s->avctx;
    const HEVCParamSets *ps = &s->ps;
    const HEVCVPS *vps = (const HEVCVPS*)ps->vps_list[sps->vps_id]->data;
    const HEVCWindow *ow = &sps->output_window;
    unsigned int num = 0, den = 0;

    avctx->pix_fmt             = sps->pix_fmt;
    avctx->coded_width         = sps->width;
    avctx->coded_height        = sps->height;
    avctx->width               = sps->width  - ow->left_offset - ow->right_offset;
    avctx->height              = sps->height - ow->top_offset  - ow->bottom_offset;
    avctx->has_b_frames        = sps->temporal_layer[sps->max_sub_layers - 1].num_reorder_pics;
    avctx->profile             = sps->ptl.general_ptl.profile_idc;
    avctx->level               = sps->ptl.general_ptl.level_idc;

    ff_set_sar(avctx, sps->vui.sar);

    if (sps->vui.video_signal_type_present_flag)
        avctx->color_range = sps->vui.video_full_range_flag ? AVCOL_RANGE_JPEG
                                                            : AVCOL_RANGE_MPEG;
    else
        avctx->color_range = AVCOL_RANGE_MPEG;

    if (sps->vui.colour_description_present_flag) {
        avctx->color_primaries = sps->vui.colour_primaries;
        avctx->color_trc       = sps->vui.transfer_characteristic;
        avctx->colorspace      = sps->vui.matrix_coeffs;
    } else {
        avctx->color_primaries = AVCOL_PRI_UNSPECIFIED;
        avctx->color_trc       = AVCOL_TRC_UNSPECIFIED;
        avctx->colorspace      = AVCOL_SPC_UNSPECIFIED;
    }

    if (vps->vps_timing_info_present_flag) {
        num = vps->vps_num_units_in_tick;
        den = vps->vps_time_scale;
    } else if (sps->vui.vui_timing_info_present_flag) {
        num = sps->vui.vui_num_units_in_tick;
        den = sps->vui.vui_time_scale;
    }

    if (num != 0 && den != 0)
        av_reduce(&avctx->framerate.den, &avctx->framerate.num,
                  num, den, 1 << 30);

    if (s->sei.alternative_transfer.present &&
        av_color_transfer_name(s->sei.alternative_transfer.preferred_transfer_characteristics) &&
        s->sei.alternative_transfer.preferred_transfer_characteristics != AVCOL_TRC_UNSPECIFIED) {
        avctx->color_trc = s->sei.alternative_transfer.preferred_transfer_characteristics;
    }
}