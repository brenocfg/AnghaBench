#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_25__ {int width; int height; TYPE_8__* priv_data; } ;
struct TYPE_16__ {int code; } ;
struct TYPE_19__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_18__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_17__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_24__ {int nbcount; int* blocks; int nby; int nbx; TYPE_7__* run_model3; TYPE_6__* op_model3; TYPE_5__* mv_model3; TYPE_10__ rc; TYPE_4__* sxy_model3; int /*<<< orphan*/  last_frame; int /*<<< orphan*/  current_frame; TYPE_3__ count_model3; TYPE_2__ fill_model3; TYPE_1__ range_model3; int /*<<< orphan*/  gb; } ;
struct TYPE_23__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_22__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_21__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
struct TYPE_20__ {int /*<<< orphan*/  dectab; int /*<<< orphan*/  cnts; int /*<<< orphan*/ * freqs; int /*<<< orphan*/  cntsum; } ;
typedef  TYPE_8__ SCPRContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_9__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int av_frame_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 scalar_t__ bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int bytestream2_get_byteu (int /*<<< orphan*/ *) ; 
 int decode_run_p (TYPE_9__*,int,int,int,int,int,int*,int*,int,int,int*,int*,int,int,int,int*,int*) ; 
 int decode_units3 (TYPE_8__*,int*,int*,int*,int*,int*) ; 
 int decode_value3 (TYPE_8__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  init_rangecoder3 (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sync_code3 (int /*<<< orphan*/ *,TYPE_10__*) ; 

__attribute__((used)) static int decompress_p3(AVCodecContext *avctx,
                         uint32_t *dst, int linesize,
                         uint32_t *prev, int plinesize)
{
    SCPRContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    int ret, temp, min, max, x, y, cx = 0, cx1 = 0;
    int backstep = linesize - avctx->width;
    int mvx = 0, mvy = 0;

    if (bytestream2_get_byte(gb) == 0)
        return 1;
    init_rangecoder3(&s->rc, gb);

    ret  = decode_value3(s, 255, &s->range_model3.cntsum,
                         s->range_model3.freqs[0],
                         s->range_model3.freqs[1],
                         s->range_model3.cnts,
                         s->range_model3.dectab, &min);
    ret |= decode_value3(s, 255, &s->range_model3.cntsum,
                         s->range_model3.freqs[0],
                         s->range_model3.freqs[1],
                         s->range_model3.cnts,
                         s->range_model3.dectab, &temp);
    if (ret < 0)
        return ret;

    min += temp << 8;
    ret |= decode_value3(s, 255, &s->range_model3.cntsum,
                         s->range_model3.freqs[0],
                         s->range_model3.freqs[1],
                         s->range_model3.cnts,
                         s->range_model3.dectab, &max);
    ret |= decode_value3(s, 255, &s->range_model3.cntsum,
                         s->range_model3.freqs[0],
                         s->range_model3.freqs[1],
                         s->range_model3.cnts,
                         s->range_model3.dectab, &temp);
    if (ret < 0)
        return ret;

    max += temp << 8;
    if (min > max || min >= s->nbcount)
        return AVERROR_INVALIDDATA;

    memset(s->blocks, 0, sizeof(*s->blocks) * s->nbcount);

    while (min <= max) {
        int fill, count;

        ret  = decode_value3(s, 4, &s->fill_model3.cntsum,
                             s->fill_model3.freqs[0],
                             s->fill_model3.freqs[1],
                             s->fill_model3.cnts,
                             s->fill_model3.dectab, &fill);
        ret |= decode_value3(s, 255, &s->count_model3.cntsum,
                             s->count_model3.freqs[0],
                             s->count_model3.freqs[1],
                             s->count_model3.cnts,
                             s->count_model3.dectab, &count);
        if (ret < 0)
            return ret;
        if (count <= 0)
            return AVERROR_INVALIDDATA;

        while (min < s->nbcount && count-- > 0) {
            s->blocks[min++] = fill;
        }
    }

    ret = av_frame_copy(s->current_frame, s->last_frame);
    if (ret < 0)
        return ret;

    for (y = 0; y < s->nby; y++) {
        for (x = 0; x < s->nbx; x++) {
            int sy1 = 0, sy2 = 16, sx1 = 0, sx2 = 16;

            if (s->blocks[y * s->nbx + x] == 0)
                continue;

            if (((s->blocks[y * s->nbx + x] + 1) & 1) > 0) {
                ret  = decode_value3(s, 15, &s->sxy_model3[0].cntsum,
                                     s->sxy_model3[0].freqs[0],
                                     s->sxy_model3[0].freqs[1],
                                     s->sxy_model3[0].cnts,
                                     s->sxy_model3[0].dectab, &sx1);
                ret |= decode_value3(s, 15, &s->sxy_model3[1].cntsum,
                                     s->sxy_model3[1].freqs[0],
                                     s->sxy_model3[1].freqs[1],
                                     s->sxy_model3[1].cnts,
                                     s->sxy_model3[1].dectab, &sy1);
                ret |= decode_value3(s, 15, &s->sxy_model3[2].cntsum,
                                     s->sxy_model3[2].freqs[0],
                                     s->sxy_model3[2].freqs[1],
                                     s->sxy_model3[2].cnts,
                                     s->sxy_model3[2].dectab, &sx2);
                ret |= decode_value3(s, 15, &s->sxy_model3[3].cntsum,
                                     s->sxy_model3[3].freqs[0],
                                     s->sxy_model3[3].freqs[1],
                                     s->sxy_model3[3].cnts,
                                     s->sxy_model3[3].dectab, &sy2);
                if (ret < 0)
                    return ret;

                sx2++;
                sy2++;
            }
            if (((s->blocks[y * s->nbx + x] + 3) & 2) > 0) {
                int i, a, b, c, j, by = y * 16, bx = x * 16;
                uint32_t code;

                a = s->rc.code & 0xFFF;
                c = 1;

                if (a < 0x800)
                    c = 0;
                b = 2048;
                if (!c)
                    b = 0;

                code = a + ((s->rc.code >> 1) & 0xFFFFF800) - b;
                while (code < 0x800000 && bytestream2_get_bytes_left(gb) > 0)
                    code = bytestream2_get_byteu(gb) | (code << 8);
                s->rc.code = code;

                sync_code3(gb, &s->rc);

                if (!c) {
                    ret  = decode_value3(s, 511, &s->mv_model3[0].cntsum,
                                         s->mv_model3[0].freqs[0],
                                         s->mv_model3[0].freqs[1],
                                         s->mv_model3[0].cnts,
                                         s->mv_model3[0].dectab, &mvx);
                    ret |= decode_value3(s, 511, &s->mv_model3[1].cntsum,
                                         s->mv_model3[1].freqs[0],
                                         s->mv_model3[1].freqs[1],
                                         s->mv_model3[1].cnts,
                                         s->mv_model3[1].dectab, &mvy);
                    if (ret < 0)
                        return ret;

                    mvx -= 256;
                    mvy -= 256;
                }

                if (by + mvy + sy1 < 0 || bx + mvx + sx1 < 0 ||
                    by + mvy + sy1 >= avctx->height || bx + mvx + sx1 >= avctx->width)
                    return AVERROR_INVALIDDATA;

                for (i = 0; i < sy2 - sy1 && (by + sy1 + i) < avctx->height && (by + mvy + sy1 + i) < avctx->height; i++) {
                    for (j = 0; j < sx2 - sx1 && (bx + sx1 + j) < avctx->width && (bx + mvx + sx1 + j) < avctx->width; j++) {
                        dst[(by + i + sy1) * linesize + bx + sx1 + j] = prev[(by + mvy + sy1 + i) * plinesize + bx + sx1 + mvx + j];
                    }
                }
            } else {
                int run, bx = x * 16 + sx1, by = y * 16 + sy1;
                uint32_t clr, ptype = 0, r, g, b;

                for (; by < y * 16 + sy2 && by < avctx->height;) {
                    ret = decode_value3(s, 5, &s->op_model3[ptype].cntsum,
                                        s->op_model3[ptype].freqs[0],
                                        s->op_model3[ptype].freqs[1],
                                        s->op_model3[ptype].cnts,
                                        s->op_model3[ptype].dectab, &ptype);
                    if (ret < 0)
                        return ret;
                    if (ptype == 0) {
                        ret = decode_units3(s, &r, &g, &b, &cx, &cx1);
                        if (ret < 0)
                            return ret;

                        clr = (b << 16) + (g << 8) + r;
                    }
                    if (ptype > 5)
                        return AVERROR_INVALIDDATA;
                    ret = decode_value3(s, 255, &s->run_model3[ptype].cntsum,
                                        s->run_model3[ptype].freqs[0],
                                        s->run_model3[ptype].freqs[1],
                                        s->run_model3[ptype].cnts,
                                        s->run_model3[ptype].dectab, &run);
                    if (ret < 0)
                        return ret;
                    if (run <= 0)
                        return AVERROR_INVALIDDATA;

                    ret = decode_run_p(avctx, ptype, run, x, y, clr,
                                       dst, prev, linesize, plinesize, &bx, &by,
                                       backstep, sx1, sx2, &cx, &cx1);
                    if (ret < 0)
                        return ret;
                }
            }
        }
    }

    return 0;
}