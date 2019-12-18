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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
typedef  int ptrdiff_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int av_clip_uintp2 (scalar_t__,int) ; 
 int /*<<< orphan*/  idct_col (scalar_t__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  idct_row (scalar_t__*) ; 

__attribute__((used)) static void hqx_idct_put(uint16_t *dst, ptrdiff_t stride,
                         int16_t *block, const uint8_t *quant)
{
    int i, j;

    for (i = 0; i < 8; i++)
        idct_col(block + i, quant + i);
    for (i = 0; i < 8; i++)
        idct_row(block + i * 8);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            int v = av_clip_uintp2(block[j + i * 8] + 0x800, 12);
            dst[j] = (v << 4) | (v >> 8);
        }
        dst += stride >> 1;
    }
}