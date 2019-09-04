#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int width; int height; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_8__ {int* linesize; scalar_t__* data; } ;
struct TYPE_7__ {int log2_chroma_w; int log2_chroma_h; } ;
typedef  TYPE_1__ AVPixFmtDescriptor ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 TYPE_1__* av_pix_fmt_desc_get (int /*<<< orphan*/ ) ; 
 int draw_horiz_band_called ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 scalar_t__ slice_byte_buffer ; 

__attribute__((used)) static void draw_horiz_band(AVCodecContext *ctx, const AVFrame *fr, int offset[4],
                            int slice_position, int type, int height)
{
    int i;
    const AVPixFmtDescriptor *pix_fmt_desc;
    int chroma_w, chroma_h;
    int shift_slice_position;
    int shift_height;

    draw_horiz_band_called = 1;

    pix_fmt_desc = av_pix_fmt_desc_get(ctx->pix_fmt);
    chroma_w = -((-ctx->width) >> pix_fmt_desc->log2_chroma_w);
    chroma_h = -((-height) >> pix_fmt_desc->log2_chroma_h);
    shift_slice_position = -((-slice_position) >> pix_fmt_desc->log2_chroma_h);
    shift_height = -((-ctx->height) >> pix_fmt_desc->log2_chroma_h);

    for (i = 0; i < height; i++) {
        memcpy(slice_byte_buffer + ctx->width * slice_position + i * ctx->width,
               fr->data[0] + offset[0] + i * fr->linesize[0], ctx->width);
    }
    for (i = 0; i < chroma_h; i++) {
        memcpy(slice_byte_buffer + ctx->width * ctx->height + chroma_w * shift_slice_position + i * chroma_w,
               fr->data[1] + offset[1] + i * fr->linesize[1], chroma_w);
    }
    for (i = 0; i < chroma_h; i++) {
        memcpy(slice_byte_buffer + ctx->width * ctx->height + chroma_w * shift_height + chroma_w * shift_slice_position + i * chroma_w,
               fr->data[2] + offset[2] + i * fr->linesize[2], chroma_w);
    }
}