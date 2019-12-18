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
typedef  scalar_t__ v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPADD_SB2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HADD_SB2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SLDI_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_W4 (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_aver_s_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_insve_d (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_insve_w (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_ldi_b (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_xori_b (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * luma_mask_arr ; 

void ff_put_h264_qpel4_mc30_msa(uint8_t *dst, const uint8_t *src,
                                ptrdiff_t stride)
{
    v16i8 src0, src1, src2, src3, res, mask0, mask1, mask2;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5;
    v8i16 res0, res1;
    v16i8 minus5b = __msa_ldi_b(-5);
    v16i8 plus20b = __msa_ldi_b(20);

    LD_SB3(&luma_mask_arr[48], 16, mask0, mask1, mask2);
    LD_SB4(src - 2, stride, src0, src1, src2, src3);
    XORI_B4_128_SB(src0, src1, src2, src3);
    VSHF_B2_SB(src0, src1, src2, src3, mask0, mask0, vec0, vec1);
    HADD_SB2_SH(vec0, vec1, res0, res1);
    VSHF_B2_SB(src0, src1, src2, src3, mask1, mask1, vec2, vec3);
    DPADD_SB2_SH(vec2, vec3, minus5b, minus5b, res0, res1);
    VSHF_B2_SB(src0, src1, src2, src3, mask2, mask2, vec4, vec5);
    DPADD_SB2_SH(vec4, vec5, plus20b, plus20b, res0, res1);
    SRARI_H2_SH(res0, res1, 5);
    SAT_SH2_SH(res0, res1, 7);
    res = __msa_pckev_b((v16i8) res1, (v16i8) res0);
    SLDI_B4_SB(src0, src0, src1, src1, src2, src2, src3, src3, 3,
               src0, src1, src2, src3);
    src0 = (v16i8) __msa_insve_w((v4i32) src0, 1, (v4i32) src1);
    src1 = (v16i8) __msa_insve_w((v4i32) src2, 1, (v4i32) src3);
    src0 = (v16i8) __msa_insve_d((v2i64) src0, 1, (v2i64) src1);
    res = __msa_aver_s_b(res, src0);
    res = (v16i8) __msa_xori_b((v16u8) res, 128);
    ST_W4(res, 0, 1, 2, 3, dst, stride);
}