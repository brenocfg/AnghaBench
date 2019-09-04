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
struct TYPE_8__ {int compression; int flags; int blocks_w; int blocks_h; int /*<<< orphan*/  chroma_quant_matrix; int /*<<< orphan*/ * size; int /*<<< orphan*/  gbyte; int /*<<< orphan*/  luma_quant_matrix; } ;
struct TYPE_7__ {int coded_width; int coded_height; TYPE_2__* priv_data; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_1__ AVCodecContext ;
typedef  TYPE_2__ AGMContext ;

/* Variables and functions */
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_quant_matrix (TYPE_2__*,int) ; 
 int decode_inter_plane (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int decode_motion_vectors (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int decode_inter(AVCodecContext *avctx, GetBitContext *gb,
                        AVFrame *frame, AVFrame *prev)
{
    AGMContext *s = avctx->priv_data;
    int ret;

    compute_quant_matrix(s, (2 * s->compression - 100) / 100.0);

    if (s->flags & 2) {
        ret = decode_motion_vectors(avctx, gb);
        if (ret < 0)
            return ret;
    }

    s->blocks_w = avctx->coded_width  >> 3;
    s->blocks_h = avctx->coded_height >> 3;

    ret = decode_inter_plane(s, gb, s->size[0], s->luma_quant_matrix, frame, prev, 0);
    if (ret < 0)
        return ret;

    bytestream2_skip(&s->gbyte, s->size[0]);

    s->blocks_w = avctx->coded_width  >> 4;
    s->blocks_h = avctx->coded_height >> 4;

    ret = decode_inter_plane(s, gb, s->size[1], s->chroma_quant_matrix, frame, prev, 2);
    if (ret < 0)
        return ret;

    bytestream2_skip(&s->gbyte, s->size[1]);

    s->blocks_w = avctx->coded_width  >> 4;
    s->blocks_h = avctx->coded_height >> 4;

    ret = decode_inter_plane(s, gb, s->size[2], s->chroma_quant_matrix, frame, prev, 1);
    if (ret < 0)
        return ret;

    return 0;
}