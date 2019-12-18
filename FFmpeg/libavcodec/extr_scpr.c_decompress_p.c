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
typedef  size_t uint32_t ;
struct TYPE_8__ {int width; int height; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int nbcount; int* blocks; int nby; int nbx; int /*<<< orphan*/ * run_model; int /*<<< orphan*/ * op_model; int /*<<< orphan*/ * mv_model; int /*<<< orphan*/ * sxy_model; int /*<<< orphan*/  last_frame; int /*<<< orphan*/  current_frame; int /*<<< orphan*/  count_model; int /*<<< orphan*/  fill_model; int /*<<< orphan*/  range_model; int /*<<< orphan*/  rc; int /*<<< orphan*/  gb; } ;
typedef  TYPE_1__ SCPRContext ;
typedef  int /*<<< orphan*/  GetByteContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int av_frame_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bytestream2_get_byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bytestream2_skip (int /*<<< orphan*/ *,int) ; 
 int decode_run_p (TYPE_2__*,size_t,int,int,int,size_t,size_t*,size_t*,int,int,int*,int*,int,int,int,int*,int*) ; 
 int decode_units (TYPE_1__*,size_t*,size_t*,size_t*,int*,int*) ; 
 int decode_value (TYPE_1__*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  init_rangecoder (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int decompress_p(AVCodecContext *avctx,
                        uint32_t *dst, int linesize,
                        uint32_t *prev, int plinesize)
{
    SCPRContext *s = avctx->priv_data;
    GetByteContext *gb = &s->gb;
    int ret, temp = 0, min, max, x, y, cx = 0, cx1 = 0;
    int backstep = linesize - avctx->width;

    if (bytestream2_get_byte(gb) == 0)
        return 1;
    bytestream2_skip(gb, 1);
    init_rangecoder(&s->rc, gb);

    ret  = decode_value(s, s->range_model, 256, 1, &min);
    ret |= decode_value(s, s->range_model, 256, 1, &temp);
    if (ret < 0)
        return ret;

    min += temp << 8;
    ret  = decode_value(s, s->range_model, 256, 1, &max);
    ret |= decode_value(s, s->range_model, 256, 1, &temp);
    if (ret < 0)
        return ret;

    max += temp << 8;
    if (min > max || min >= s->nbcount)
        return AVERROR_INVALIDDATA;

    memset(s->blocks, 0, sizeof(*s->blocks) * s->nbcount);

    while (min <= max) {
        int fill, count;

        ret  = decode_value(s, s->fill_model,  5,   10, &fill);
        ret |= decode_value(s, s->count_model, 256, 20, &count);
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

            if (((s->blocks[y * s->nbx + x] - 1) & 1) > 0) {
                ret  = decode_value(s, s->sxy_model[0], 16, 100, &sx1);
                ret |= decode_value(s, s->sxy_model[1], 16, 100, &sy1);
                ret |= decode_value(s, s->sxy_model[2], 16, 100, &sx2);
                ret |= decode_value(s, s->sxy_model[3], 16, 100, &sy2);
                if (ret < 0)
                    return ret;

                sx2++;
                sy2++;
            }
            if (((s->blocks[y * s->nbx + x] - 1) & 2) > 0) {
                int i, j, by = y * 16, bx = x * 16;
                int mvx, mvy;

                ret  = decode_value(s, s->mv_model[0], 512, 100, &mvx);
                ret |= decode_value(s, s->mv_model[1], 512, 100, &mvy);
                if (ret < 0)
                    return ret;

                mvx -= 256;
                mvy -= 256;

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
                uint32_t r, g, b, clr, ptype = 0;

                for (; by < y * 16 + sy2 && by < avctx->height;) {
                    ret = decode_value(s, s->op_model[ptype], 6, 1000, &ptype);
                    if (ret < 0)
                        return ret;
                    if (ptype == 0) {
                        ret = decode_units(s, &r, &g, &b, &cx, &cx1);
                        if (ret < 0)
                            return ret;

                        clr = (b << 16) + (g << 8) + r;
                    }
                    if (ptype > 5)
                        return AVERROR_INVALIDDATA;
                    ret = decode_value(s, s->run_model[ptype], 256, 400, &run);
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