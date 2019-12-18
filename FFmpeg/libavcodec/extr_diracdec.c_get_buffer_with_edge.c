#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ height; scalar_t__ width; int /*<<< orphan*/  pix_fmt; } ;
struct TYPE_7__ {int* linesize; scalar_t__ height; scalar_t__ width; scalar_t__* data; } ;
typedef  TYPE_1__ AVFrame ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int EDGE_WIDTH ; 
 int av_pix_fmt_get_chroma_sub_sample (int /*<<< orphan*/ ,int*,int*) ; 
 int ff_get_buffer (TYPE_2__*,TYPE_1__*,int) ; 

__attribute__((used)) static int get_buffer_with_edge(AVCodecContext *avctx, AVFrame *f, int flags)
{
    int ret, i;
    int chroma_x_shift, chroma_y_shift;
    ret = av_pix_fmt_get_chroma_sub_sample(avctx->pix_fmt, &chroma_x_shift,
                                           &chroma_y_shift);
    if (ret < 0)
        return ret;

    f->width  = avctx->width  + 2 * EDGE_WIDTH;
    f->height = avctx->height + 2 * EDGE_WIDTH + 2;
    ret = ff_get_buffer(avctx, f, flags);
    if (ret < 0)
        return ret;

    for (i = 0; f->data[i]; i++) {
        int offset = (EDGE_WIDTH >> (i && i<3 ? chroma_y_shift : 0)) *
                     f->linesize[i] + 32;
        f->data[i] += offset;
    }
    f->width  = avctx->width;
    f->height = avctx->height;

    return 0;
}