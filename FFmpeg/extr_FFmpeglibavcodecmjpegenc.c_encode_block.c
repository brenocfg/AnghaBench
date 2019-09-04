#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int16_t ;
struct TYPE_7__ {int /*<<< orphan*/ * huff_code_ac_chrominance; int /*<<< orphan*/ * huff_size_ac_chrominance; int /*<<< orphan*/  huff_code_dc_chrominance; int /*<<< orphan*/  huff_size_dc_chrominance; int /*<<< orphan*/ * huff_code_ac_luminance; int /*<<< orphan*/ * huff_size_ac_luminance; int /*<<< orphan*/  huff_code_dc_luminance; int /*<<< orphan*/  huff_size_dc_luminance; } ;
struct TYPE_5__ {int* permutated; } ;
struct TYPE_6__ {int* last_dc; int* block_last_index; int /*<<< orphan*/  pb; TYPE_1__ intra_scantable; TYPE_3__* mjpeg_ctx; } ;
typedef  TYPE_2__ MpegEncContext ;
typedef  TYPE_3__ MJpegContext ;

/* Variables and functions */
 int av_log2_16bit (int) ; 
 int /*<<< orphan*/  ff_mjpeg_encode_dc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_sbits (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void encode_block(MpegEncContext *s, int16_t *block, int n)
{
    int mant, nbits, code, i, j;
    int component, dc, run, last_index, val;
    MJpegContext *m = s->mjpeg_ctx;
    uint8_t *huff_size_ac;
    uint16_t *huff_code_ac;

    /* DC coef */
    component = (n <= 3 ? 0 : (n&1) + 1);
    dc = block[0]; /* overflow is impossible */
    val = dc - s->last_dc[component];
    if (n < 4) {
        ff_mjpeg_encode_dc(&s->pb, val, m->huff_size_dc_luminance, m->huff_code_dc_luminance);
        huff_size_ac = m->huff_size_ac_luminance;
        huff_code_ac = m->huff_code_ac_luminance;
    } else {
        ff_mjpeg_encode_dc(&s->pb, val, m->huff_size_dc_chrominance, m->huff_code_dc_chrominance);
        huff_size_ac = m->huff_size_ac_chrominance;
        huff_code_ac = m->huff_code_ac_chrominance;
    }
    s->last_dc[component] = dc;

    /* AC coefs */

    run = 0;
    last_index = s->block_last_index[n];
    for(i=1;i<=last_index;i++) {
        j = s->intra_scantable.permutated[i];
        val = block[j];
        if (val == 0) {
            run++;
        } else {
            while (run >= 16) {
                put_bits(&s->pb, huff_size_ac[0xf0], huff_code_ac[0xf0]);
                run -= 16;
            }
            mant = val;
            if (val < 0) {
                val = -val;
                mant--;
            }

            nbits= av_log2_16bit(val) + 1;
            code = (run << 4) | nbits;

            put_bits(&s->pb, huff_size_ac[code], huff_code_ac[code]);

            put_sbits(&s->pb, nbits, mant);
            run = 0;
        }
    }

    /* output EOB only if not already 64 values */
    if (last_index < 63 || run != 0)
        put_bits(&s->pb, huff_size_ac[0], huff_code_ac[0]);
}