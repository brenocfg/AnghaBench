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
typedef  int uint8_t ;
struct TYPE_4__ {int channels; int sample_rate; int bit_rate; } ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int AVERROR_PATCHWELCOME ; 
 int AV_RB16 (int const*) ; 
 int AV_RB32 (int const*) ; 
 int BLOCK_SAMPLES ; 
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  COEFF_BITS ; 
 int INT_MAX ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ff_adx_calculate_coeffs (int,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ memcmp (int const*,char*,int) ; 

int ff_adx_decode_header(AVCodecContext *avctx, const uint8_t *buf,
                         int bufsize, int *header_size, int *coeff)
{
    int offset, cutoff;

    if (bufsize < 24)
        return AVERROR_INVALIDDATA;

    if (AV_RB16(buf) != 0x8000)
        return AVERROR_INVALIDDATA;
    offset = AV_RB16(buf + 2) + 4;

    /* if copyright string is within the provided data, validate it */
    if (bufsize >= offset && offset >= 6 && memcmp(buf + offset - 6, "(c)CRI", 6))
        return AVERROR_INVALIDDATA;

    /* check for encoding=3 block_size=18, sample_size=4 */
    if (buf[4] != 3 || buf[5] != 18 || buf[6] != 4) {
        avpriv_request_sample(avctx, "Support for this ADX format");
        return AVERROR_PATCHWELCOME;
    }

    /* channels */
    avctx->channels = buf[7];
    if (avctx->channels <= 0 || avctx->channels > 2)
        return AVERROR_INVALIDDATA;

    /* sample rate */
    avctx->sample_rate = AV_RB32(buf + 8);
    if (avctx->sample_rate < 1 ||
        avctx->sample_rate > INT_MAX / (avctx->channels * BLOCK_SIZE * 8))
        return AVERROR_INVALIDDATA;

    /* bit rate */
    avctx->bit_rate = avctx->sample_rate * avctx->channels * BLOCK_SIZE * 8 / BLOCK_SAMPLES;

    /* LPC coefficients */
    if (coeff) {
        cutoff = AV_RB16(buf + 16);
        ff_adx_calculate_coeffs(cutoff, avctx->sample_rate, COEFF_BITS, coeff);
    }

    *header_size = offset;
    return 0;
}