#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_13__ {int picture_type; int postprocflag; int rangered; int deblockEnable; int /*<<< orphan*/  pquant; int /*<<< orphan*/  maxbframes; int /*<<< orphan*/  syncmarker; int /*<<< orphan*/  multires; int /*<<< orphan*/  range_mapuv; int /*<<< orphan*/  range_mapuv_flag; int /*<<< orphan*/  range_mapy; int /*<<< orphan*/  range_mapy_flag; int /*<<< orphan*/  fastuvmc; int /*<<< orphan*/  loopfilter; int /*<<< orphan*/  vstransform; int /*<<< orphan*/  overlap; int /*<<< orphan*/  extended_dmv; int /*<<< orphan*/  extended_mv; int /*<<< orphan*/  quantizer; int /*<<< orphan*/  refdist_flag; int /*<<< orphan*/  panscan_flag; int /*<<< orphan*/  dquant; int /*<<< orphan*/  psf; int /*<<< orphan*/  finterpflag; int /*<<< orphan*/  tfcntrflag; int /*<<< orphan*/  interlace; int /*<<< orphan*/  pulldown; scalar_t__ frame_coding_mode; scalar_t__ slice_count; void* forward_reference; void* backward_reference; } ;
struct TYPE_10__ {TYPE_4__ vc1; } ;
struct vdpau_picture_context {TYPE_1__ info; } ;
typedef  void* VdpVideoSurface ;
typedef  TYPE_4__ VdpPictureInfoVC1 ;
struct TYPE_12__ {int /*<<< orphan*/  f; } ;
struct TYPE_11__ {int /*<<< orphan*/  f; } ;
struct TYPE_16__ {int pict_type; int /*<<< orphan*/  max_b_frames; int /*<<< orphan*/  loop_filter; TYPE_3__ last_picture; int /*<<< orphan*/  last_picture_ptr; TYPE_2__ next_picture; int /*<<< orphan*/  next_picture_ptr; TYPE_6__* current_picture_ptr; } ;
struct TYPE_14__ {int postprocflag; int rangered; int rangeredfrm; int /*<<< orphan*/  pq; TYPE_7__ s; int /*<<< orphan*/  resync_marker; int /*<<< orphan*/  multires; int /*<<< orphan*/  range_mapuv; int /*<<< orphan*/  range_mapuv_flag; int /*<<< orphan*/  range_mapy; int /*<<< orphan*/  range_mapy_flag; int /*<<< orphan*/  fastuvmc; int /*<<< orphan*/  vstransform; int /*<<< orphan*/  overlap; int /*<<< orphan*/  extended_dmv; int /*<<< orphan*/  extended_mv; int /*<<< orphan*/  quantizer_mode; int /*<<< orphan*/  refdist_flag; int /*<<< orphan*/  panscanflag; int /*<<< orphan*/  dquant; int /*<<< orphan*/  psf; int /*<<< orphan*/  finterpflag; int /*<<< orphan*/  tfcntrflag; int /*<<< orphan*/  interlace; int /*<<< orphan*/  broadcast; scalar_t__ fcm; scalar_t__ bi_type; } ;
typedef  TYPE_5__ VC1Context ;
struct TYPE_17__ {TYPE_5__* priv_data; } ;
struct TYPE_15__ {struct vdpau_picture_context* hwaccel_picture_private; } ;
typedef  TYPE_6__ Picture ;
typedef  TYPE_7__ MpegEncContext ;
typedef  TYPE_8__ AVCodecContext ;

/* Variables and functions */
#define  AV_PICTURE_TYPE_B 129 
#define  AV_PICTURE_TYPE_P 128 
 void* VDP_INVALID_HANDLE ; 
 int /*<<< orphan*/  assert (int) ; 
 int ff_vdpau_common_start_frame (struct vdpau_picture_context*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 void* ff_vdpau_get_surface_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vdpau_vc1_start_frame(AVCodecContext *avctx,
                                 const uint8_t *buffer, uint32_t size)
{
    VC1Context * const v  = avctx->priv_data;
    MpegEncContext * const s = &v->s;
    Picture *pic          = s->current_picture_ptr;
    struct vdpau_picture_context *pic_ctx = pic->hwaccel_picture_private;
    VdpPictureInfoVC1 *info = &pic_ctx->info.vc1;
    VdpVideoSurface ref;

    /*  fill LvPictureInfoVC1 struct */
    info->forward_reference  = VDP_INVALID_HANDLE;
    info->backward_reference = VDP_INVALID_HANDLE;

    switch (s->pict_type) {
    case AV_PICTURE_TYPE_B:
        if (s->next_picture_ptr) {
        ref = ff_vdpau_get_surface_id(s->next_picture.f);
        assert(ref != VDP_INVALID_HANDLE);
        info->backward_reference = ref;
        }
        /* fall-through */
    case AV_PICTURE_TYPE_P:
        if (s->last_picture_ptr) {
        ref = ff_vdpau_get_surface_id(s->last_picture.f);
        assert(ref != VDP_INVALID_HANDLE);
        info->forward_reference  = ref;
        }
    }

    info->slice_count       = 0;
    if (v->bi_type)
        info->picture_type  = 4;
    else
        info->picture_type  = s->pict_type - 1 + s->pict_type / 3;

    info->frame_coding_mode = v->fcm ? (v->fcm + 1) : 0;
    info->postprocflag      = v->postprocflag;
    info->pulldown          = v->broadcast;
    info->interlace         = v->interlace;
    info->tfcntrflag        = v->tfcntrflag;
    info->finterpflag       = v->finterpflag;
    info->psf               = v->psf;
    info->dquant            = v->dquant;
    info->panscan_flag      = v->panscanflag;
    info->refdist_flag      = v->refdist_flag;
    info->quantizer         = v->quantizer_mode;
    info->extended_mv       = v->extended_mv;
    info->extended_dmv      = v->extended_dmv;
    info->overlap           = v->overlap;
    info->vstransform       = v->vstransform;
    info->loopfilter        = v->s.loop_filter;
    info->fastuvmc          = v->fastuvmc;
    info->range_mapy_flag   = v->range_mapy_flag;
    info->range_mapy        = v->range_mapy;
    info->range_mapuv_flag  = v->range_mapuv_flag;
    info->range_mapuv       = v->range_mapuv;
    /* Specific to simple/main profile only */
    info->multires          = v->multires;
    info->syncmarker        = v->resync_marker;
    info->rangered          = v->rangered | (v->rangeredfrm << 1);
    info->maxbframes        = v->s.max_b_frames;
    info->deblockEnable     = v->postprocflag & 1;
    info->pquant            = v->pq;

    return ff_vdpau_common_start_frame(pic_ctx, buffer, size);
}