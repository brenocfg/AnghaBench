#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_12__ {int height; int width; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int* linesize; scalar_t__* data; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* idct_put ) (scalar_t__,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_10__ {scalar_t__ hi; int lo; int factor; int /*<<< orphan*/ * block; TYPE_1__ idsp; } ;
typedef  TYPE_2__ IMM4Context ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 TYPE_8__ cbplo_tab ; 
 int decode_blocks (TYPE_4__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int,unsigned int) ; 
 unsigned int get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_cbphi (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* intra_cb ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_intra(AVCodecContext *avctx, GetBitContext *gb, AVFrame *frame)
{
    IMM4Context *s = avctx->priv_data;
    int ret, x, y, offset = 0;

    if (s->hi == 0) {
        if (s->lo > 2)
            return AVERROR_INVALIDDATA;
        s->factor = intra_cb[s->lo];
    } else {
        s->factor = s->lo * 2;
    }

    if (s->hi) {
        offset = s->factor;
        offset >>= 1;
        if (!(offset & 1))
            offset--;
    }

    for (y = 0; y < avctx->height; y += 16) {
        for (x = 0; x < avctx->width; x += 16) {
            unsigned flag, cbphi, cbplo;

            cbplo = get_vlc2(gb, cbplo_tab.table, cbplo_tab.bits, 1) >> 4;
            flag = get_bits1(gb);

            cbphi = get_cbphi(gb, 1);

            ret = decode_blocks(avctx, gb, cbplo | (cbphi << 2), 0, offset, flag);
            if (ret < 0)
                return ret;

            s->idsp.idct_put(frame->data[0] + y * frame->linesize[0] + x,
                             frame->linesize[0], s->block[0]);
            s->idsp.idct_put(frame->data[0] + y * frame->linesize[0] + x + 8,
                             frame->linesize[0], s->block[1]);
            s->idsp.idct_put(frame->data[0] + (y + 8) * frame->linesize[0] + x,
                             frame->linesize[0], s->block[2]);
            s->idsp.idct_put(frame->data[0] + (y + 8) * frame->linesize[0] + x + 8,
                             frame->linesize[0], s->block[3]);
            s->idsp.idct_put(frame->data[1] + (y >> 1) * frame->linesize[1] + (x >> 1),
                             frame->linesize[1], s->block[4]);
            s->idsp.idct_put(frame->data[2] + (y >> 1) * frame->linesize[2] + (x >> 1),
                             frame->linesize[2], s->block[5]);
        }
    }

    return 0;
}