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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  hevc_idct_8x32_column_msa (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hevc_idct_transpose_32x8_to_8x32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hevc_idct_transpose_8x32_to_32x8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hevc_idct_32x32_msa(int16_t *coeffs)
{
    uint8_t row_cnt, col_cnt;
    int16_t *src = coeffs;
    int16_t tmp_buf[8 * 32 + 31];
    int16_t *tmp_buf_ptr = tmp_buf + 31;
    uint8_t round;
    uint8_t buf_pitch;

    /* Align pointer to 64 byte boundary */
    tmp_buf_ptr = (int16_t *)(((uintptr_t) tmp_buf_ptr) & ~(uintptr_t) 63);

    /* column transform */
    round = 7;
    buf_pitch = 32;
    for (col_cnt = 0; col_cnt < 4; col_cnt++) {
        /* process 8x32 blocks */
        hevc_idct_8x32_column_msa((coeffs + col_cnt * 8), buf_pitch, round);
    }

    /* row transform */
    round = 12;
    buf_pitch = 8;
    for (row_cnt = 0; row_cnt < 4; row_cnt++) {
        /* process 32x8 blocks */
        src = (coeffs + 32 * 8 * row_cnt);

        hevc_idct_transpose_32x8_to_8x32(src, tmp_buf_ptr);
        hevc_idct_8x32_column_msa(tmp_buf_ptr, buf_pitch, round);
        hevc_idct_transpose_8x32_to_32x8(tmp_buf_ptr, src);
    }
}