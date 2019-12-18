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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 scalar_t__ av_clip_uint8 (scalar_t__) ; 
 int /*<<< orphan*/  wmv2_idct_col (scalar_t__*) ; 
 int /*<<< orphan*/  wmv2_idct_row (scalar_t__*) ; 

__attribute__((used)) static void wmv2_idct_add_c(uint8_t *dest, ptrdiff_t line_size, int16_t *block)
{
    int i;

    for (i = 0; i < 64; i += 8)
        wmv2_idct_row(block + i);
    for (i = 0; i < 8; i++)
        wmv2_idct_col(block + i);

    for (i = 0; i < 8; i++) {
        dest[0] = av_clip_uint8(dest[0] + block[0]);
        dest[1] = av_clip_uint8(dest[1] + block[1]);
        dest[2] = av_clip_uint8(dest[2] + block[2]);
        dest[3] = av_clip_uint8(dest[3] + block[3]);
        dest[4] = av_clip_uint8(dest[4] + block[4]);
        dest[5] = av_clip_uint8(dest[5] + block[5]);
        dest[6] = av_clip_uint8(dest[6] + block[6]);
        dest[7] = av_clip_uint8(dest[7] + block[7]);
        dest += line_size;
        block += 8;
    }
}