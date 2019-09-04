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
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmv2_idct_col (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmv2_idct_row (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wmv2_idct_put_c(uint8_t *dest, ptrdiff_t line_size, int16_t *block)
{
    int i;

    for (i = 0; i < 64; i += 8)
        wmv2_idct_row(block + i);
    for (i = 0; i < 8; i++)
        wmv2_idct_col(block + i);

    for (i = 0; i < 8; i++) {
        dest[0] = av_clip_uint8(block[0]);
        dest[1] = av_clip_uint8(block[1]);
        dest[2] = av_clip_uint8(block[2]);
        dest[3] = av_clip_uint8(block[3]);
        dest[4] = av_clip_uint8(block[4]);
        dest[5] = av_clip_uint8(block[5]);
        dest[6] = av_clip_uint8(block[6]);
        dest[7] = av_clip_uint8(block[7]);
        dest += line_size;
        block += 8;
    }
}