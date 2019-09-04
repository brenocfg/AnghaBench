#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
struct TYPE_17__ {int output_bit_depth; int /*<<< orphan*/  frame_rate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_3__ davs2_seq_info_t ;
struct TYPE_18__ {int bytes_per_sample; int type; int* widths; int* lines; int* strides; scalar_t__* planes; } ;
typedef  TYPE_4__ davs2_picture_t ;
struct TYPE_21__ {int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  framerate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_5__* priv_data; } ;
struct TYPE_20__ {int* linesize; int /*<<< orphan*/  format; int /*<<< orphan*/  pts; int /*<<< orphan*/  height; int /*<<< orphan*/  width; scalar_t__* data; TYPE_13__** buf; int /*<<< orphan*/  pict_type; } ;
struct TYPE_16__ {int /*<<< orphan*/  pts; } ;
struct TYPE_15__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_19__ {TYPE_2__ out_frame; TYPE_1__ headerset; } ;
struct TYPE_14__ {scalar_t__ data; } ;
typedef  TYPE_5__ DAVS2Context ;
typedef  TYPE_6__ AVFrame ;
typedef  TYPE_7__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXTERNAL ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_B ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_I ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_P ; 
 int /*<<< orphan*/  AV_PICTURE_TYPE_S ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P ; 
 int /*<<< orphan*/  AV_PIX_FMT_YUV420P10 ; 
 int DAVS2_GOT_HEADER ; 
#define  DAVS2_PIC_B 133 
#define  DAVS2_PIC_F 132 
#define  DAVS2_PIC_G 131 
#define  DAVS2_PIC_I 130 
#define  DAVS2_PIC_P 129 
#define  DAVS2_PIC_S 128 
 int /*<<< orphan*/  ENOMEM ; 
 TYPE_13__* av_buffer_alloc (int) ; 
 int /*<<< orphan*/  av_d2q (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int davs2_dump_frames(AVCodecContext *avctx, davs2_picture_t *pic, int *got_frame,
                             davs2_seq_info_t *headerset, int ret_type, AVFrame *frame)
{
    DAVS2Context *cad    = avctx->priv_data;
    int bytes_per_sample = pic->bytes_per_sample;
    int plane = 0;
    int line  = 0;

    if (!headerset) {
        *got_frame = 0;
        return 0;
    }

    if (!pic || ret_type == DAVS2_GOT_HEADER) {
        avctx->width     = headerset->width;
        avctx->height    = headerset->height;
        avctx->pix_fmt   = headerset->output_bit_depth == 10 ?
                           AV_PIX_FMT_YUV420P10 : AV_PIX_FMT_YUV420P;

        avctx->framerate = av_d2q(headerset->frame_rate,4096);
        *got_frame = 0;
        return 0;
    }

    switch (pic->type) {
    case DAVS2_PIC_I:
    case DAVS2_PIC_G:
        frame->pict_type = AV_PICTURE_TYPE_I;
        break;
    case DAVS2_PIC_P:
    case DAVS2_PIC_S:
        frame->pict_type = AV_PICTURE_TYPE_P;
        break;
    case DAVS2_PIC_B:
        frame->pict_type = AV_PICTURE_TYPE_B;
        break;
    case DAVS2_PIC_F:
        frame->pict_type = AV_PICTURE_TYPE_S;
        break;
    default:
        av_log(avctx, AV_LOG_ERROR, "Decoder error: unknown frame type\n");
        return AVERROR_EXTERNAL;
    }

    for (plane = 0; plane < 3; ++plane) {
        int size_line = pic->widths[plane] * bytes_per_sample;
        frame->buf[plane]  = av_buffer_alloc(size_line * pic->lines[plane]);

        if (!frame->buf[plane]){
            av_log(avctx, AV_LOG_ERROR, "Decoder error: allocation failure, can't dump frames.\n");
            return AVERROR(ENOMEM);
        }

        frame->data[plane]     = frame->buf[plane]->data;
        frame->linesize[plane] = size_line;

        for (line = 0; line < pic->lines[plane]; ++line)
            memcpy(frame->data[plane] + line * size_line,
                   pic->planes[plane] + line * pic->strides[plane],
                   pic->widths[plane] * bytes_per_sample);
    }

    frame->width     = cad->headerset.width;
    frame->height    = cad->headerset.height;
    frame->pts       = cad->out_frame.pts;
    frame->format    = avctx->pix_fmt;

    *got_frame = 1;
    return 0;
}