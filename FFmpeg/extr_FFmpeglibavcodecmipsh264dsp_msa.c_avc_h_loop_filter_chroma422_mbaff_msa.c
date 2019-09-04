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
typedef  int /*<<< orphan*/  v8i16 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_LPF_H_2BYTE_CHROMA_422 (int /*<<< orphan*/ *,int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SH (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __msa_copy_s_h (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __msa_fill_b (int) ; 

__attribute__((used)) static void avc_h_loop_filter_chroma422_mbaff_msa(uint8_t *src, int32_t stride,
                                                  int32_t alpha_in,
                                                  int32_t beta_in,
                                                  int8_t *tc0)
{
    int32_t col, tc_val;
    int16_t out0, out1;
    v16u8 alpha, beta, res;

    alpha = (v16u8) __msa_fill_b(alpha_in);
    beta = (v16u8) __msa_fill_b(beta_in);

    for (col = 0; col < 4; col++) {
        tc_val = (tc0[col] - 1) + 1;

        if (tc_val <= 0) {
            src += 4 * stride;
            continue;
        }

        AVC_LPF_H_2BYTE_CHROMA_422(src, stride, tc_val, alpha, beta, res);

        out0 = __msa_copy_s_h((v8i16) res, 0);
        out1 = __msa_copy_s_h((v8i16) res, 1);

        SH(out0, (src - 1));
        src += stride;
        SH(out1, (src - 1));
        src += stride;
    }
}