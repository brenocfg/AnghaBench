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
typedef  int v8i16 ;
typedef  int v4i32 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  BUTTERFLY_4 (int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  BUTTERFLY_8 (int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CLIP_SH4_0_255 (int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_B4_SH (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH8 (int*,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B4_SB (int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_H4_SH (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SRA_4V (int,int,int,int,int) ; 
 int /*<<< orphan*/  ST8x4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_SH8 (int,int,int,int,int,int,int,int,int*,int) ; 
 int /*<<< orphan*/  TRANSPOSE8x8_SH_SH (int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  UNPCK_SH_SW (int,int,int) ; 

__attribute__((used)) static void avc_idct8_addblk_msa(uint8_t *dst, int16_t *src, int32_t dst_stride)
{
    v8i16 src0, src1, src2, src3, src4, src5, src6, src7;
    v8i16 vec0, vec1, vec2, vec3;
    v8i16 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    v8i16 res0, res1, res2, res3, res4, res5, res6, res7;
    v4i32 tmp0_r, tmp1_r, tmp2_r, tmp3_r, tmp4_r, tmp5_r, tmp6_r, tmp7_r;
    v4i32 tmp0_l, tmp1_l, tmp2_l, tmp3_l, tmp4_l, tmp5_l, tmp6_l, tmp7_l;
    v4i32 vec0_r, vec1_r, vec2_r, vec3_r, vec0_l, vec1_l, vec2_l, vec3_l;
    v4i32 res0_r, res1_r, res2_r, res3_r, res4_r, res5_r, res6_r, res7_r;
    v4i32 res0_l, res1_l, res2_l, res3_l, res4_l, res5_l, res6_l, res7_l;
    v16i8 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v8i16 zeros = { 0 };

    src[0] += 32;

    LD_SH8(src, 8, src0, src1, src2, src3, src4, src5, src6, src7);
    ST_SH8(zeros, zeros, zeros, zeros, zeros, zeros, zeros, zeros, src, 8);

    vec0 = src0 + src4;
    vec1 = src0 - src4;
    vec2 = src2 >> 1;
    vec2 = vec2 - src6;
    vec3 = src6 >> 1;
    vec3 = src2 + vec3;

    BUTTERFLY_4(vec0, vec1, vec2, vec3, tmp0, tmp1, tmp2, tmp3);

    vec0 = src7 >> 1;
    vec0 = src5 - vec0 - src3 - src7;
    vec1 = src3 >> 1;
    vec1 = src1 - vec1 + src7 - src3;
    vec2 = src5 >> 1;
    vec2 = vec2 - src1 + src7 + src5;
    vec3 = src1 >> 1;
    vec3 = vec3 + src3 + src5 + src1;
    tmp4 = vec3 >> 2;
    tmp4 += vec0;
    tmp5 = vec2 >> 2;
    tmp5 += vec1;
    tmp6 = vec1 >> 2;
    tmp6 -= vec2;
    tmp7 = vec0 >> 2;
    tmp7 = vec3 - tmp7;

    BUTTERFLY_8(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7,
                res0, res1, res2, res3, res4, res5, res6, res7);
    TRANSPOSE8x8_SH_SH(res0, res1, res2, res3, res4, res5, res6, res7,
                       res0, res1, res2, res3, res4, res5, res6, res7);
    UNPCK_SH_SW(res0, tmp0_r, tmp0_l);
    UNPCK_SH_SW(res1, tmp1_r, tmp1_l);
    UNPCK_SH_SW(res2, tmp2_r, tmp2_l);
    UNPCK_SH_SW(res3, tmp3_r, tmp3_l);
    UNPCK_SH_SW(res4, tmp4_r, tmp4_l);
    UNPCK_SH_SW(res5, tmp5_r, tmp5_l);
    UNPCK_SH_SW(res6, tmp6_r, tmp6_l);
    UNPCK_SH_SW(res7, tmp7_r, tmp7_l);
    BUTTERFLY_4(tmp0_r, tmp0_l, tmp4_l, tmp4_r, vec0_r, vec0_l, vec1_l, vec1_r);

    vec2_r = tmp2_r >> 1;
    vec2_l = tmp2_l >> 1;
    vec2_r -= tmp6_r;
    vec2_l -= tmp6_l;
    vec3_r = tmp6_r >> 1;
    vec3_l = tmp6_l >> 1;
    vec3_r += tmp2_r;
    vec3_l += tmp2_l;

    BUTTERFLY_4(vec0_r, vec1_r, vec2_r, vec3_r, tmp0_r, tmp2_r, tmp4_r, tmp6_r);
    BUTTERFLY_4(vec0_l, vec1_l, vec2_l, vec3_l, tmp0_l, tmp2_l, tmp4_l, tmp6_l);

    vec0_r = tmp7_r >> 1;
    vec0_l = tmp7_l >> 1;
    vec0_r = tmp5_r - vec0_r - tmp3_r - tmp7_r;
    vec0_l = tmp5_l - vec0_l - tmp3_l - tmp7_l;
    vec1_r = tmp3_r >> 1;
    vec1_l = tmp3_l >> 1;
    vec1_r = tmp1_r - vec1_r + tmp7_r - tmp3_r;
    vec1_l = tmp1_l - vec1_l + tmp7_l - tmp3_l;
    vec2_r = tmp5_r >> 1;
    vec2_l = tmp5_l >> 1;
    vec2_r = vec2_r - tmp1_r + tmp7_r + tmp5_r;
    vec2_l = vec2_l - tmp1_l + tmp7_l + tmp5_l;
    vec3_r = tmp1_r >> 1;
    vec3_l = tmp1_l >> 1;
    vec3_r = vec3_r + tmp3_r + tmp5_r + tmp1_r;
    vec3_l = vec3_l + tmp3_l + tmp5_l + tmp1_l;
    tmp1_r = vec3_r >> 2;
    tmp1_l = vec3_l >> 2;
    tmp1_r += vec0_r;
    tmp1_l += vec0_l;
    tmp3_r = vec2_r >> 2;
    tmp3_l = vec2_l >> 2;
    tmp3_r += vec1_r;
    tmp3_l += vec1_l;
    tmp5_r = vec1_r >> 2;
    tmp5_l = vec1_l >> 2;
    tmp5_r -= vec2_r;
    tmp5_l -= vec2_l;
    tmp7_r = vec0_r >> 2;
    tmp7_l = vec0_l >> 2;
    tmp7_r = vec3_r - tmp7_r;
    tmp7_l = vec3_l - tmp7_l;

    BUTTERFLY_4(tmp0_r, tmp0_l, tmp7_l, tmp7_r, res0_r, res0_l, res7_l, res7_r);
    BUTTERFLY_4(tmp2_r, tmp2_l, tmp5_l, tmp5_r, res1_r, res1_l, res6_l, res6_r);
    BUTTERFLY_4(tmp4_r, tmp4_l, tmp3_l, tmp3_r, res2_r, res2_l, res5_l, res5_r);
    BUTTERFLY_4(tmp6_r, tmp6_l, tmp1_l, tmp1_r, res3_r, res3_l, res4_l, res4_r);
    SRA_4V(res0_r, res0_l, res1_r, res1_l, 6);
    SRA_4V(res2_r, res2_l, res3_r, res3_l, 6);
    SRA_4V(res4_r, res4_l, res5_r, res5_l, 6);
    SRA_4V(res6_r, res6_l, res7_r, res7_l, 6);
    PCKEV_H4_SH(res0_l, res0_r, res1_l, res1_r, res2_l, res2_r, res3_l, res3_r,
                res0, res1, res2, res3);
    PCKEV_H4_SH(res4_l, res4_r, res5_l, res5_r, res6_l, res6_r, res7_l, res7_r,
                res4, res5, res6, res7);
    LD_SB8(dst, dst_stride, dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
    ILVR_B4_SH(zeros, dst0, zeros, dst1, zeros, dst2, zeros, dst3,
               tmp0, tmp1, tmp2, tmp3);
    ILVR_B4_SH(zeros, dst4, zeros, dst5, zeros, dst6, zeros, dst7,
               tmp4, tmp5, tmp6, tmp7);
    ADD4(res0, tmp0, res1, tmp1, res2, tmp2, res3, tmp3,
         res0, res1, res2, res3);
    ADD4(res4, tmp4, res5, tmp5, res6, tmp6, res7, tmp7,
         res4, res5, res6, res7);
    CLIP_SH4_0_255(res0, res1, res2, res3);
    CLIP_SH4_0_255(res4, res5, res6, res7);
    PCKEV_B4_SB(res1, res0, res3, res2, res5, res4, res7, res6,
                dst0, dst1, dst2, dst3);
    ST8x4_UB(dst0, dst1, dst, dst_stride);
    dst += (4 * dst_stride);
    ST8x4_UB(dst2, dst3, dst, dst_stride);
}