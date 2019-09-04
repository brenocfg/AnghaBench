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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  pixel ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  scalar_t__ dctcoef ;

/* Variables and functions */
 int /*<<< orphan*/  ff_h264_idct4x4_addblk_dc_msa (int*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ff_h264_idct_add_msa (int*,int /*<<< orphan*/ *,int) ; 
 size_t* scan8 ; 

void ff_h264_idct_add16_msa(uint8_t *dst,
                            const int32_t *blk_offset,
                            int16_t *block, int32_t dst_stride,
                            const uint8_t nzc[15 * 8])
{
    int32_t i;

    for (i = 0; i < 16; i++) {
        int32_t nnz = nzc[scan8[i]];

        if (nnz) {
            if (nnz == 1 && ((dctcoef *) block)[i * 16])
                ff_h264_idct4x4_addblk_dc_msa(dst + blk_offset[i],
                                              block + i * 16 * sizeof(pixel),
                                              dst_stride);
            else
                ff_h264_idct_add_msa(dst + blk_offset[i],
                                     block + i * 16 * sizeof(pixel),
                                     dst_stride);
        }
    }
}