#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_4__ {int /*<<< orphan*/ * cur_dec; scalar_t__ data_end; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ Bundle ;
typedef  int /*<<< orphan*/  AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  CHECK_READ_VAL (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int read_dcs(AVCodecContext *avctx, GetBitContext *gb, Bundle *b,
                    int start_bits, int has_sign)
{
    int i, j, len, len2, bsize, sign, v, v2;
    int16_t *dst     = (int16_t*)b->cur_dec;
    int16_t *dst_end = (int16_t*)b->data_end;

    CHECK_READ_VAL(gb, b, len);
    if (get_bits_left(gb) < start_bits - has_sign)
        return AVERROR_INVALIDDATA;
    v = get_bits(gb, start_bits - has_sign);
    if (v && has_sign) {
        sign = -get_bits1(gb);
        v = (v ^ sign) - sign;
    }
    if (dst_end - dst < 1)
        return AVERROR_INVALIDDATA;
    *dst++ = v;
    len--;
    for (i = 0; i < len; i += 8) {
        len2 = FFMIN(len - i, 8);
        if (dst_end - dst < len2)
            return AVERROR_INVALIDDATA;
        bsize = get_bits(gb, 4);
        if (bsize) {
            for (j = 0; j < len2; j++) {
                v2 = get_bits(gb, bsize);
                if (v2) {
                    sign = -get_bits1(gb);
                    v2 = (v2 ^ sign) - sign;
                }
                v += v2;
                *dst++ = v;
                if (v < -32768 || v > 32767) {
                    av_log(avctx, AV_LOG_ERROR, "DC value went out of bounds: %d\n", v);
                    return AVERROR_INVALIDDATA;
                }
            }
        } else {
            for (j = 0; j < len2; j++)
                *dst++ = v;
        }
    }

    b->cur_dec = (uint8_t*)dst;
    return 0;
}