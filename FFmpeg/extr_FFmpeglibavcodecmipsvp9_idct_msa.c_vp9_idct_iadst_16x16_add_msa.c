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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  vp9_iadst16_1d_columns_addblk_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vp9_idct16_1d_columns_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vp9_idct_iadst_16x16_add_msa(int16_t *input, uint8_t *dst,
                                         int32_t dst_stride, int32_t eob)
{
    int32_t i;
    int16_t out[16 * 16];
    int16_t *out_ptr = &out[0];

    /* transform rows */
    for (i = 0; i < 2; i++) {
        /* process 8 * 16 block */
        vp9_idct16_1d_columns_msa((input + (i << 3)), (out_ptr + (i << 7)));
    }

    /* transform columns */
    for (i = 0; i < 2; i++) {
        /* process 8 * 16 block */
        vp9_iadst16_1d_columns_addblk_msa((out_ptr + (i << 3)),
                                          (dst + (i << 3)), dst_stride);
    }
}