#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int16_t ;
typedef  enum TwinVQFrameType { ____Placeholder_TwinVQFrameType } TwinVQFrameType ;
struct TYPE_3__ {int* n_div; int** length; int* length_change; int* bits_main_spec_change; int*** bits_main_spec; size_t** permut; } ;
typedef  TYPE_1__ TwinVQContext ;

/* Variables and functions */

__attribute__((used)) static void dequant(TwinVQContext *tctx, const uint8_t *cb_bits, float *out,
                    enum TwinVQFrameType ftype,
                    const int16_t *cb0, const int16_t *cb1, int cb_len)
{
    int pos = 0;
    int i, j;

    for (i = 0; i < tctx->n_div[ftype]; i++) {
        int tmp0, tmp1;
        int sign0 = 1;
        int sign1 = 1;
        const int16_t *tab0, *tab1;
        int length = tctx->length[ftype][i >= tctx->length_change[ftype]];
        int bitstream_second_part = (i >= tctx->bits_main_spec_change[ftype]);

        int bits = tctx->bits_main_spec[0][ftype][bitstream_second_part];
        tmp0 = *cb_bits++;
        if (bits == 7) {
            if (tmp0 & 0x40)
                sign0 = -1;
            tmp0 &= 0x3F;
        }

        bits = tctx->bits_main_spec[1][ftype][bitstream_second_part];
        tmp1 = *cb_bits++;
        if (bits == 7) {
            if (tmp1 & 0x40)
                sign1 = -1;
            tmp1 &= 0x3F;
        }

        tab0 = cb0 + tmp0 * cb_len;
        tab1 = cb1 + tmp1 * cb_len;

        for (j = 0; j < length; j++)
            out[tctx->permut[ftype][pos + j]] = sign0 * tab0[j] +
                                                sign1 * tab1[j];

        pos += length;
    }
}