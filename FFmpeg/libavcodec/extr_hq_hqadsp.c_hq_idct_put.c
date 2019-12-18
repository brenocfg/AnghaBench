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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_clip_uint8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idct_col (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idct_row (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hq_idct_put(uint8_t *dst, int stride, int16_t *block)
{
    int i, j;

    for (i = 0; i < 8; i++)
        idct_row(block + i * 8);
    for (i = 0; i < 8; i++)
        idct_col(block + i);

    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++)
            dst[j] = av_clip_uint8(block[j + i * 8]);
        dst += stride;
    }
}