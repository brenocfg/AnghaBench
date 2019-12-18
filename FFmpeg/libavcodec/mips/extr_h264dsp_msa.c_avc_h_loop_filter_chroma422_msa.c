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
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_LPF_H_CHROMA_422 (int /*<<< orphan*/ *,int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_H4 (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __msa_fill_b (int) ; 

__attribute__((used)) static void avc_h_loop_filter_chroma422_msa(uint8_t *src, int32_t stride,
                                            int32_t alpha_in, int32_t beta_in,
                                            int8_t *tc0)
{
    int32_t col, tc_val;
    v16u8 alpha, beta, res;

    alpha = (v16u8) __msa_fill_b(alpha_in);
    beta = (v16u8) __msa_fill_b(beta_in);

    for (col = 0; col < 4; col++) {
        tc_val = (tc0[col] - 1) + 1;

        if (tc_val <= 0) {
            src += (4 * stride);
            continue;
        }

        AVC_LPF_H_CHROMA_422(src, stride, tc_val, alpha, beta, res);
        ST_H4(res, 0, 1, 2, 3, (src - 1), stride);
        src += (4 * stride);
    }
}