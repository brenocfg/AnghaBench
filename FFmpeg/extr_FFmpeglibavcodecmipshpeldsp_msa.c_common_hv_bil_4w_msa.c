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
typedef  scalar_t__ v8u16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HADD_UB3_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B3_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB (int const*) ; 
 int /*<<< orphan*/  LD_SB2 (int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLDI_B3_0_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRARI_H2_UH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  __msa_copy_u_w (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __msa_pckev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void common_hv_bil_4w_msa(const uint8_t *src, int32_t src_stride,
                                 uint8_t *dst, int32_t dst_stride,
                                 uint8_t height)
{
    uint8_t loop_cnt;
    uint32_t res0, res1;
    v16i8 src0, src1, src2, src0_sld1, src1_sld1, src2_sld1;
    v16u8 src0_r, src1_r, src2_r, res;
    v8u16 add0, add1, add2, sum0, sum1;

    src0 = LD_SB(src);
    src += src_stride;

    for (loop_cnt = (height >> 1); loop_cnt--;) {
        LD_SB2(src, src_stride, src1, src2);
        src += (2 * src_stride);

        SLDI_B3_0_SB(src0, src1, src2, src0_sld1, src1_sld1, src2_sld1, 1);
        ILVR_B3_UB(src0_sld1, src0, src1_sld1, src1, src2_sld1, src2,
                   src0_r, src1_r, src2_r);
        HADD_UB3_UH(src0_r, src1_r, src2_r, add0, add1, add2);
        ADD2(add0, add1, add1, add2, sum0, sum1);
        SRARI_H2_UH(sum0, sum1, 2);
        res = (v16u8) __msa_pckev_b((v16i8) sum1, (v16i8) sum0);
        res0 = __msa_copy_u_w((v4i32) res, 0);
        res1 = __msa_copy_u_w((v4i32) res, 2);
        SW(res0, dst);
        dst += dst_stride;
        SW(res1, dst);
        dst += dst_stride;

        src0 = src2;
    }
}