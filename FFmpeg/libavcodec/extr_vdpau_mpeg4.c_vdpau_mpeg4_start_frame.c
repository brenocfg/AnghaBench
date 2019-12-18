#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_21__ {int vop_coding_type; int* trd; int* trb; int resync_marker_disable; int interlaced; int short_video_header; int /*<<< orphan*/ * non_intra_quantizer_matrix; int /*<<< orphan*/ * intra_quantizer_matrix; int /*<<< orphan*/  top_field_first; int /*<<< orphan*/  alternate_vertical_scan_flag; int /*<<< orphan*/  rounding_control; int /*<<< orphan*/  quarter_sample; int /*<<< orphan*/  quant_type; int /*<<< orphan*/  vop_fcode_backward; int /*<<< orphan*/  vop_fcode_forward; int /*<<< orphan*/  vop_time_increment_resolution; void* forward_reference; void* backward_reference; } ;
struct TYPE_15__ {TYPE_7__ mpeg4; } ;
struct vdpau_picture_context {TYPE_1__ info; } ;
typedef  void* VdpVideoSurface ;
typedef  TYPE_7__ VdpPictureInfoMPEG4Part2 ;
struct TYPE_17__ {int /*<<< orphan*/  f; } ;
struct TYPE_16__ {int /*<<< orphan*/  f; } ;
struct TYPE_23__ {int pict_type; int pp_time; int pb_time; int pp_field_time; int pb_field_time; int /*<<< orphan*/ * inter_matrix; int /*<<< orphan*/ * intra_matrix; int /*<<< orphan*/  top_field_first; int /*<<< orphan*/  alternate_scan; int /*<<< orphan*/  no_rounding; int /*<<< orphan*/  quarter_sample; int /*<<< orphan*/  mpeg_quant; int /*<<< orphan*/  progressive_sequence; int /*<<< orphan*/  b_code; int /*<<< orphan*/  f_code; TYPE_5__* avctx; TYPE_3__ last_picture; TYPE_2__ next_picture; TYPE_8__* current_picture_ptr; } ;
struct TYPE_22__ {struct vdpau_picture_context* hwaccel_picture_private; } ;
struct TYPE_20__ {scalar_t__ id; } ;
struct TYPE_18__ {int /*<<< orphan*/  num; } ;
struct TYPE_19__ {TYPE_4__ framerate; } ;
struct TYPE_14__ {TYPE_6__* codec; TYPE_10__* priv_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  resync_marker; TYPE_9__ m; } ;
typedef  TYPE_8__ Picture ;
typedef  TYPE_9__ MpegEncContext ;
typedef  TYPE_10__ Mpeg4DecContext ;
typedef  TYPE_11__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H263 ; 
#define  AV_PICTURE_TYPE_B 129 
#define  AV_PICTURE_TYPE_P 128 
 void* VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int ff_vdpau_add_buffer (struct vdpau_picture_context*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_vdpau_common_start_frame (struct vdpau_picture_context*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* ff_vdpau_get_surface_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdpau_mpeg4_start_frame(AVCodecContext *avctx,
                                   const uint8_t *buffer, uint32_t size)
{
    Mpeg4DecContext *ctx = avctx->priv_data;
    MpegEncContext * const s = &ctx->m;
    Picture *pic             = s->current_picture_ptr;
    struct vdpau_picture_context *pic_ctx = pic->hwaccel_picture_private;
    VdpPictureInfoMPEG4Part2 *info = &pic_ctx->info.mpeg4;
    VdpVideoSurface ref;
    int i;

    /* fill VdpPictureInfoMPEG4Part2 struct */
    info->forward_reference  = VDP_INVALID_HANDLE;
    info->backward_reference = VDP_INVALID_HANDLE;
    info->vop_coding_type    = 0;

    switch (s->pict_type) {
    case AV_PICTURE_TYPE_B:
        ref = ff_vdpau_get_surface_id(s->next_picture.f);
        assert(ref != VDP_INVALID_HANDLE);
        info->backward_reference = ref;
        info->vop_coding_type    = 2;
        /* fall-through */
    case AV_PICTURE_TYPE_P:
        ref = ff_vdpau_get_surface_id(s->last_picture.f);
        assert(ref != VDP_INVALID_HANDLE);
        info->forward_reference  = ref;
    }

    info->trd[0]                            = s->pp_time;
    info->trb[0]                            = s->pb_time;
    info->trd[1]                            = s->pp_field_time >> 1;
    info->trb[1]                            = s->pb_field_time >> 1;
    info->vop_time_increment_resolution     = s->avctx->framerate.num;
    info->vop_fcode_forward                 = s->f_code;
    info->vop_fcode_backward                = s->b_code;
    info->resync_marker_disable             = !ctx->resync_marker;
    info->interlaced                        = !s->progressive_sequence;
    info->quant_type                        = s->mpeg_quant;
    info->quarter_sample                    = s->quarter_sample;
    info->short_video_header                = avctx->codec->id == AV_CODEC_ID_H263;
    info->rounding_control                  = s->no_rounding;
    info->alternate_vertical_scan_flag      = s->alternate_scan;
    info->top_field_first                   = s->top_field_first;
    for (i = 0; i < 64; ++i) {
        info->intra_quantizer_matrix[i]     = s->intra_matrix[i];
        info->non_intra_quantizer_matrix[i] = s->inter_matrix[i];
    }

    ff_vdpau_common_start_frame(pic_ctx, buffer, size);
    return ff_vdpau_add_buffer(pic_ctx, buffer, size);
}