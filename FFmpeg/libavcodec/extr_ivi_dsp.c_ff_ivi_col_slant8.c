#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IVI_INV_SLANT8 (int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int,int,int,int,int,int,int) ; 

void ff_ivi_col_slant8(const int32_t *in, int16_t *out, ptrdiff_t pitch, const uint8_t *flags)
{
    int     i, row2, row4, row8;
    int     t0, t1, t2, t3, t4, t5, t6, t7, t8;

    row2 = pitch << 1;
    row4 = pitch << 2;
    row8 = pitch << 3;

#define COMPENSATE(x) (((x) + 1)>>1)
    for (i = 0; i < 8; i++) {
        if (flags[i]) {
            IVI_INV_SLANT8(in[0], in[8], in[16], in[24], in[32], in[40], in[48], in[56],
                           out[0], out[pitch], out[row2], out[row2 + pitch], out[row4],
                           out[row4 + pitch],  out[row4 + row2], out[row8 - pitch],
                           t0, t1, t2, t3, t4, t5, t6, t7, t8);
        } else {
            out[0] = out[pitch] = out[row2] = out[row2 + pitch] = out[row4] =
            out[row4 + pitch] =  out[row4 + row2] = out[row8 - pitch] = 0;
        }

        in++;
        out++;
    }
#undef COMPENSATE
}