#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  pix_fmt; scalar_t__ has_b_frames; int /*<<< orphan*/  coded_height; int /*<<< orphan*/  coded_width; TYPE_4__* priv_data; } ;
struct TYPE_12__ {int* idct_permutation; } ;
struct TYPE_14__ {int low_delay; int* intra_matrix; int* chroma_intra_matrix; int* inter_matrix; int* chroma_inter_matrix; int progressive_sequence; int progressive_frame; int frame_pred_frame_dct; int chroma_format; scalar_t__ codec_tag; int swap_uv; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_2__* avctx; int /*<<< orphan*/  codec_id; scalar_t__ first_field; int /*<<< orphan*/  picture_structure; TYPE_1__ idsp; int /*<<< orphan*/  out_format; } ;
struct TYPE_15__ {int mpeg_enc_ctx_allocated; int save_progressive_seq; int /*<<< orphan*/  save_height; int /*<<< orphan*/  save_width; TYPE_3__ mpeg_enc_ctx; } ;
struct TYPE_13__ {int /*<<< orphan*/  codec_id; } ;
typedef  TYPE_3__ MpegEncContext ;
typedef  TYPE_4__ Mpeg1Context ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_CODEC_ID_MPEG1VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_RL32 (char*) ; 
 int /*<<< orphan*/  FMT_MPEG1 ; 
 int /*<<< orphan*/  PICT_FRAME ; 
 int* ff_mpeg1_default_intra_matrix ; 
 int* ff_mpeg1_default_non_intra_matrix ; 
 int /*<<< orphan*/  ff_mpv_common_end (TYPE_3__*) ; 
 int ff_mpv_common_init (TYPE_3__*) ; 
 int /*<<< orphan*/  ff_mpv_idct_init (TYPE_3__*) ; 
 int /*<<< orphan*/  mpeg_get_pixelformat (TYPE_5__*) ; 
 int /*<<< orphan*/  setup_hwaccel_for_pixfmt (TYPE_5__*) ; 

__attribute__((used)) static int vcr2_init_sequence(AVCodecContext *avctx)
{
    Mpeg1Context *s1  = avctx->priv_data;
    MpegEncContext *s = &s1->mpeg_enc_ctx;
    int i, v, ret;

    /* start new MPEG-1 context decoding */
    s->out_format = FMT_MPEG1;
    if (s1->mpeg_enc_ctx_allocated) {
        ff_mpv_common_end(s);
        s1->mpeg_enc_ctx_allocated = 0;
    }
    s->width            = avctx->coded_width;
    s->height           = avctx->coded_height;
    avctx->has_b_frames = 0; // true?
    s->low_delay        = 1;

    avctx->pix_fmt = mpeg_get_pixelformat(avctx);
    setup_hwaccel_for_pixfmt(avctx);

    ff_mpv_idct_init(s);
    if ((ret = ff_mpv_common_init(s)) < 0)
        return ret;
    s1->mpeg_enc_ctx_allocated = 1;

    for (i = 0; i < 64; i++) {
        int j = s->idsp.idct_permutation[i];
        v = ff_mpeg1_default_intra_matrix[i];
        s->intra_matrix[j]        = v;
        s->chroma_intra_matrix[j] = v;

        v = ff_mpeg1_default_non_intra_matrix[i];
        s->inter_matrix[j]        = v;
        s->chroma_inter_matrix[j] = v;
    }

    s->progressive_sequence  = 1;
    s->progressive_frame     = 1;
    s->picture_structure     = PICT_FRAME;
    s->first_field           = 0;
    s->frame_pred_frame_dct  = 1;
    s->chroma_format         = 1;
    if (s->codec_tag == AV_RL32("BW10")) {
        s->codec_id              = s->avctx->codec_id = AV_CODEC_ID_MPEG1VIDEO;
    } else {
        s->swap_uv = 1; // in case of xvmc we need to swap uv for each MB
        s->codec_id              = s->avctx->codec_id = AV_CODEC_ID_MPEG2VIDEO;
    }
    s1->save_width           = s->width;
    s1->save_height          = s->height;
    s1->save_progressive_seq = s->progressive_sequence;
    return 0;
}