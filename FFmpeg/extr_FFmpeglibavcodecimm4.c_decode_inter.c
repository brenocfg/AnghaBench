#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
struct TYPE_13__ {int height; int width; TYPE_2__* priv_data; } ;
struct TYPE_12__ {int* linesize; scalar_t__* data; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* idct_add ) (scalar_t__,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* idct_put ) (scalar_t__,int,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {scalar_t__ hi; int lo; int factor; int /*<<< orphan*/ * block; TYPE_1__ idsp; } ;
typedef  TYPE_2__ IMM4Context ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 TYPE_9__ blktype_tab ; 
 int /*<<< orphan*/  copy_block16 (scalar_t__,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  copy_block8 (scalar_t__,scalar_t__,int,int,int) ; 
 int decode_blocks (TYPE_4__*,int /*<<< orphan*/ *,unsigned int,int,int,unsigned int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_cbphi (int /*<<< orphan*/ *,int) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int* inter_cb ; 
 int /*<<< orphan*/  skip_bits1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int decode_inter(AVCodecContext *avctx, GetBitContext *gb,
                        AVFrame *frame, AVFrame *prev)
{
    IMM4Context *s = avctx->priv_data;
    int ret, x, y, offset = 0;

    if (s->hi == 0) {
        if (s->lo > 2)
            return AVERROR_INVALIDDATA;
        s->factor = inter_cb[s->lo];
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
            int reverse, intra_block, value;
            unsigned cbphi, cbplo, flag2 = 0;

            if (get_bits1(gb)) {
                copy_block16(frame->data[0] + y * frame->linesize[0] + x,
                             prev->data[0] + y * prev->linesize[0] + x,
                             frame->linesize[0], prev->linesize[0], 16);
                copy_block8(frame->data[1] + (y >> 1) * frame->linesize[1] + (x >> 1),
                            prev->data[1] + (y >> 1) * prev->linesize[1] + (x >> 1),
                            frame->linesize[1], prev->linesize[1], 8);
                copy_block8(frame->data[2] + (y >> 1) * frame->linesize[2] + (x >> 1),
                            prev->data[2] + (y >> 1) * prev->linesize[2] + (x >> 1),
                            frame->linesize[2], prev->linesize[2], 8);
                continue;
            }

            value = get_vlc2(gb, blktype_tab.table, blktype_tab.bits, 1);
            if (value < 0)
                return AVERROR_INVALIDDATA;

            intra_block = value & 0x07;
            reverse = intra_block == 3;
            if (reverse)
                flag2 = get_bits1(gb);

            cbplo = value >> 4;
            cbphi = get_cbphi(gb, reverse);
            if (intra_block) {
                ret = decode_blocks(avctx, gb, cbplo | (cbphi << 2), 0, offset, flag2);
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
            } else {
                flag2 = get_bits1(gb);
                skip_bits1(gb);
                ret = decode_blocks(avctx, gb, cbplo | (cbphi << 2), 1, offset, flag2);
                if (ret < 0)
                    return ret;

                copy_block16(frame->data[0] + y * frame->linesize[0] + x,
                             prev->data[0] + y * prev->linesize[0] + x,
                             frame->linesize[0], prev->linesize[0], 16);
                copy_block8(frame->data[1] + (y >> 1) * frame->linesize[1] + (x >> 1),
                            prev->data[1] + (y >> 1) * prev->linesize[1] + (x >> 1),
                            frame->linesize[1], prev->linesize[1], 8);
                copy_block8(frame->data[2] + (y >> 1) * frame->linesize[2] + (x >> 1),
                            prev->data[2] + (y >> 1) * prev->linesize[2] + (x >> 1),
                            frame->linesize[2], prev->linesize[2], 8);

                s->idsp.idct_add(frame->data[0] + y * frame->linesize[0] + x,
                                 frame->linesize[0], s->block[0]);
                s->idsp.idct_add(frame->data[0] + y * frame->linesize[0] + x + 8,
                                 frame->linesize[0], s->block[1]);
                s->idsp.idct_add(frame->data[0] + (y + 8) * frame->linesize[0] + x,
                                 frame->linesize[0], s->block[2]);
                s->idsp.idct_add(frame->data[0] + (y + 8) * frame->linesize[0] + x + 8,
                                 frame->linesize[0], s->block[3]);
                s->idsp.idct_add(frame->data[1] + (y >> 1) * frame->linesize[1] + (x >> 1),
                                 frame->linesize[1], s->block[4]);
                s->idsp.idct_add(frame->data[2] + (y >> 1) * frame->linesize[2] + (x >> 1),
                                 frame->linesize[2], s->block[5]);
            }
        }
    }

    return 0;
}