#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int int64_t ;
typedef  int int16_t ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  gb; int /*<<< orphan*/  bc; } ;
typedef  TYPE_1__ PixletContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  align_get_bits (int /*<<< orphan*/ *) ; 
 int av_mod_uintp2 (int,int) ; 
 int /*<<< orphan*/  bytestream2_get_bytes_left (int /*<<< orphan*/ *) ; 
 int ff_clz (int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_count (int /*<<< orphan*/ *) ; 
 unsigned int get_unary (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int init_get_bits8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* show_bits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skip_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_high_coeffs(AVCodecContext *avctx, uint8_t *src, int16_t *dst,
                            int size, int c, int a, int d,
                            int width, ptrdiff_t stride)
{
    PixletContext *ctx = avctx->priv_data;
    GetBitContext *bc = &ctx->bc;
    unsigned cnt1, shbits, rlen, nbits, length, i = 0, j = 0, k;
    int ret, escape, pfx, value, yflag, xflag, flag = 0;
    int64_t state = 3, tmp;

    ret = init_get_bits8(bc, src, bytestream2_get_bytes_left(&ctx->gb));
    if (ret < 0)
        return ret;

    if (a ^ (a >> 31)) {
        nbits = 33 - ff_clz(a ^ (a >> 31));
        if (nbits > 16)
            return AVERROR_INVALIDDATA;
    } else {
        nbits = 1;
    }

    length = 25 - nbits;

    while (i < size) {
        if (state >> 8 != -3)
            value = ff_clz((state >> 8) + 3) ^ 0x1F;
        else
            value = -1;

        cnt1 = get_unary(bc, 0, length);
        if (cnt1 >= length) {
            cnt1 = get_bits(bc, nbits);
        } else {
            pfx = 14 + ((((uint64_t)(value - 14)) >> 32) & (value - 14));
            if (pfx < 1 || pfx > 25)
                return AVERROR_INVALIDDATA;
            cnt1 *= (1 << pfx) - 1;
            shbits = show_bits(bc, pfx);
            if (shbits <= 1) {
                skip_bits(bc, pfx - 1);
            } else {
                skip_bits(bc, pfx);
                cnt1 += shbits - 1;
            }
        }

        xflag = flag + cnt1;
        yflag = xflag;

        if (flag + cnt1 == 0) {
            value = 0;
        } else {
            xflag &= 1u;
            tmp    = (int64_t)c * ((yflag + 1) >> 1) + (c >> 1);
            value  = xflag + (tmp ^ -xflag);
        }

        i++;
        dst[j++] = value;
        if (j == width) {
            j    = 0;
            dst += stride;
        }
        state += (int64_t)d * (uint64_t)yflag - ((int64_t)(d * (uint64_t)state) >> 8);

        flag = 0;

        if ((uint64_t)state > 0xFF / 4 || i >= size)
            continue;

        pfx    = ((state + 8) >> 5) + (state ? ff_clz(state) : 32) - 24;
        escape = av_mod_uintp2(16383, pfx);
        cnt1   = get_unary(bc, 0, 8);
        if (cnt1 < 8) {
            if (pfx < 1 || pfx > 25)
                return AVERROR_INVALIDDATA;

            value = show_bits(bc, pfx);
            if (value > 1) {
                skip_bits(bc, pfx);
                rlen = value + escape * cnt1 - 1;
            } else {
                skip_bits(bc, pfx - 1);
                rlen = escape * cnt1;
            }
        } else {
            if (get_bits1(bc))
                value = get_bits(bc, 16);
            else
                value = get_bits(bc, 8);

            rlen = value + 8 * escape;
        }

        if (rlen > 0xFFFF || i + rlen > size)
            return AVERROR_INVALIDDATA;
        i += rlen;

        for (k = 0; k < rlen; k++) {
            dst[j++] = 0;
            if (j == width) {
                j    = 0;
                dst += stride;
            }
        }

        state = 0;
        flag  = rlen < 0xFFFF ? 1 : 0;
    }

    align_get_bits(bc);
    return get_bits_count(bc) >> 3;
}