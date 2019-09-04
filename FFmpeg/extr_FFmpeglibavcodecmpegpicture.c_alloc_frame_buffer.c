#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_14__ ;
typedef  struct TYPE_18__   TYPE_12__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_12__* f; } ;
struct TYPE_23__ {scalar_t__ codec_id; TYPE_1__* hwaccel; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  codec; } ;
struct TYPE_22__ {TYPE_12__* f; TYPE_14__* hwaccel_priv_buf; scalar_t__ hwaccel_picture_private; scalar_t__ reference; TYPE_6__ tf; } ;
struct TYPE_21__ {int /*<<< orphan*/  edge_emu_buffer; } ;
struct TYPE_20__ {scalar_t__ frame_priv_data_size; } ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_18__ {int* linesize; int /*<<< orphan*/  format; scalar_t__ height; scalar_t__ width; scalar_t__* data; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_2__ ScratchpadContext ;
typedef  TYPE_3__ Picture ;
typedef  int /*<<< orphan*/  MotionEstContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_MSS2 ; 
 scalar_t__ AV_CODEC_ID_VC1IMAGE ; 
 scalar_t__ AV_CODEC_ID_WMV3IMAGE ; 
 int /*<<< orphan*/  AV_GET_BUFFER_FLAG_REF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int EDGE_WIDTH ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_14__* av_buffer_allocz (scalar_t__) ; 
 int av_codec_is_encoder (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,...) ; 
 int av_pix_fmt_count_planes (int /*<<< orphan*/ ) ; 
 int avcodec_default_get_buffer2 (TYPE_4__*,TYPE_12__*,int /*<<< orphan*/ ) ; 
 int ff_mpeg_framesize_alloc (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  ff_mpeg_unref_picture (TYPE_4__*,TYPE_3__*) ; 
 int ff_thread_get_buffer (TYPE_4__*,TYPE_6__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_frame_buffer(AVCodecContext *avctx,  Picture *pic,
                              MotionEstContext *me, ScratchpadContext *sc,
                              int chroma_x_shift, int chroma_y_shift,
                              int linesize, int uvlinesize)
{
    int edges_needed = av_codec_is_encoder(avctx->codec);
    int r, ret;

    pic->tf.f = pic->f;
    if (avctx->codec_id != AV_CODEC_ID_WMV3IMAGE &&
        avctx->codec_id != AV_CODEC_ID_VC1IMAGE  &&
        avctx->codec_id != AV_CODEC_ID_MSS2) {
        if (edges_needed) {
            pic->f->width  = avctx->width  + 2 * EDGE_WIDTH;
            pic->f->height = avctx->height + 2 * EDGE_WIDTH;
        }

        r = ff_thread_get_buffer(avctx, &pic->tf,
                                 pic->reference ? AV_GET_BUFFER_FLAG_REF : 0);
    } else {
        pic->f->width  = avctx->width;
        pic->f->height = avctx->height;
        pic->f->format = avctx->pix_fmt;
        r = avcodec_default_get_buffer2(avctx, pic->f, 0);
    }

    if (r < 0 || !pic->f->buf[0]) {
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed (%d %p)\n",
               r, pic->f->data[0]);
        return -1;
    }

    if (edges_needed) {
        int i;
        for (i = 0; pic->f->data[i]; i++) {
            int offset = (EDGE_WIDTH >> (i ? chroma_y_shift : 0)) *
                         pic->f->linesize[i] +
                         (EDGE_WIDTH >> (i ? chroma_x_shift : 0));
            pic->f->data[i] += offset;
        }
        pic->f->width  = avctx->width;
        pic->f->height = avctx->height;
    }

    if (avctx->hwaccel) {
        assert(!pic->hwaccel_picture_private);
        if (avctx->hwaccel->frame_priv_data_size) {
            pic->hwaccel_priv_buf = av_buffer_allocz(avctx->hwaccel->frame_priv_data_size);
            if (!pic->hwaccel_priv_buf) {
                av_log(avctx, AV_LOG_ERROR, "alloc_frame_buffer() failed (hwaccel private data allocation)\n");
                return -1;
            }
            pic->hwaccel_picture_private = pic->hwaccel_priv_buf->data;
        }
    }

    if ((linesize   &&   linesize != pic->f->linesize[0]) ||
        (uvlinesize && uvlinesize != pic->f->linesize[1])) {
        av_log(avctx, AV_LOG_ERROR,
               "get_buffer() failed (stride changed: linesize=%d/%d uvlinesize=%d/%d)\n",
               linesize,   pic->f->linesize[0],
               uvlinesize, pic->f->linesize[1]);
        ff_mpeg_unref_picture(avctx, pic);
        return -1;
    }

    if (av_pix_fmt_count_planes(pic->f->format) > 2 &&
        pic->f->linesize[1] != pic->f->linesize[2]) {
        av_log(avctx, AV_LOG_ERROR,
               "get_buffer() failed (uv stride mismatch)\n");
        ff_mpeg_unref_picture(avctx, pic);
        return -1;
    }

    if (!sc->edge_emu_buffer &&
        (ret = ff_mpeg_framesize_alloc(avctx, me, sc,
                                       pic->f->linesize[0])) < 0) {
        av_log(avctx, AV_LOG_ERROR,
               "get_buffer() failed to allocate context scratch buffers.\n");
        ff_mpeg_unref_picture(avctx, pic);
        return ret;
    }

    return 0;
}