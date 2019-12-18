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
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPADD_SB4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HADD_SB4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SLDI_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_SB4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_aver_s_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_ldi_b (int) ; 
 int /*<<< orphan*/ * luma_mask_arr ; 

void ff_put_h264_qpel16_mc10_msa(uint8_t *dst, const uint8_t *src,
                                 ptrdiff_t stride)
{
    uint32_t loop_cnt;
    v16i8 dst0, dst1, dst2, dst3, src0, src1, src2, src3, src4, src5, src6;
    v16i8 mask0, mask1, mask2, mask3, mask4, mask5, src7, vec11;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, vec8, vec9, vec10;
    v8i16 res0, res1, res2, res3, res4, res5, res6, res7;
    v16i8 minus5b = __msa_ldi_b(-5);
    v16i8 plus20b = __msa_ldi_b(20);

    LD_SB3(&luma_mask_arr[0], 16, mask0, mask1, mask2);
    mask3 = mask0 + 8;
    mask4 = mask1 + 8;
    mask5 = mask2 + 8;
    src -= 2;

    for (loop_cnt = 4; loop_cnt--;) {
        LD_SB2(src, 16, src0, src1);
        src += stride;
        LD_SB2(src, 16, src2, src3);
        src += stride;
        LD_SB2(src, 16, src4, src5);
        src += stride;
        LD_SB2(src, 16, src6, src7);
        src += stride;

        XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);
        VSHF_B2_SB(src0, src0, src0, src1, mask0, mask3, vec0, vec3);
        VSHF_B2_SB(src2, src2, src2, src3, mask0, mask3, vec6, vec9);
        VSHF_B2_SB(src0, src0, src0, src1, mask1, mask4, vec1, vec4);
        VSHF_B2_SB(src2, src2, src2, src3, mask1, mask4, vec7, vec10);
        VSHF_B2_SB(src0, src0, src0, src1, mask2, mask5, vec2, vec5);
        VSHF_B2_SB(src2, src2, src2, src3, mask2, mask5, vec8, vec11);
        HADD_SB4_SH(vec0, vec3, vec6, vec9, res0, res1, res2, res3);
        DPADD_SB4_SH(vec1, vec4, vec7, vec10, minus5b, minus5b, minus5b,
                     minus5b, res0, res1, res2, res3);
        DPADD_SB4_SH(vec2, vec5, vec8, vec11, plus20b, plus20b, plus20b,
                     plus20b, res0, res1, res2, res3);
        VSHF_B2_SB(src4, src4, src4, src5, mask0, mask3, vec0, vec3);
        VSHF_B2_SB(src6, src6, src6, src7, mask0, mask3, vec6, vec9);
        VSHF_B2_SB(src4, src4, src4, src5, mask1, mask4, vec1, vec4);
        VSHF_B2_SB(src6, src6, src6, src7, mask1, mask4, vec7, vec10);
        VSHF_B2_SB(src4, src4, src4, src5, mask2, mask5, vec2, vec5);
        VSHF_B2_SB(src6, src6, src6, src7, mask2, mask5, vec8, vec11);
        HADD_SB4_SH(vec0, vec3, vec6, vec9, res4, res5, res6, res7);
        DPADD_SB4_SH(vec1, vec4, vec7, vec10, minus5b, minus5b, minus5b,
                     minus5b, res4, res5, res6, res7);
        DPADD_SB4_SH(vec2, vec5, vec8, vec11, plus20b, plus20b, plus20b,
                     plus20b, res4, res5, res6, res7);
        SLDI_B4_SB(src1, src0, src3, src2, src5, src4, src7, src6, 2,
                   src0, src2, src4, src6);
        SRARI_H4_SH(res0, res1, res2, res3, 5);
        SRARI_H4_SH(res4, res5, res6, res7, 5);
        SAT_SH4_SH(res0, res1, res2, res3, 7);
        SAT_SH4_SH(res4, res5, res6, res7, 7);
        PCKEV_B2_SB(res1, res0, res3, res2, dst0, dst1);
        PCKEV_B2_SB(res5, res4, res7, res6, dst2, dst3);
        dst0 = __msa_aver_s_b(dst0, src0);
        dst1 = __msa_aver_s_b(dst1, src2);
        dst2 = __msa_aver_s_b(dst2, src4);
        dst3 = __msa_aver_s_b(dst3, src6);
        XORI_B4_128_SB(dst0, dst1, dst2, dst3);
        ST_SB4(dst0, dst1, dst2, dst3, dst, stride);
        dst += (4 * stride);
    }
}