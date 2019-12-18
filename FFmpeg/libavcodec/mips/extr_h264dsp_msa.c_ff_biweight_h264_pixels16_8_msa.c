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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH8_0_255 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_UB8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B8_128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_dpadd_s_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_b (int) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_ilvev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_biweight_h264_pixels16_8_msa(uint8_t *dst, uint8_t *src,
                                     ptrdiff_t stride, int height,
                                     int log2_denom, int weight_dst,
                                     int weight_src, int offset_in)
{
    v16i8 src_wgt, dst_wgt, wgt;
    v16u8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16u8 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 vec8, vec9, vec10, vec11, vec12, vec13, vec14, vec15;
    v8i16 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    v8i16 tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15;
    v8i16 denom, offset;

    offset_in = (unsigned) ((offset_in + 1) | 1) << log2_denom;
    offset_in += (128 * (weight_src + weight_dst));

    src_wgt = __msa_fill_b(weight_src);
    dst_wgt = __msa_fill_b(weight_dst);
    offset = __msa_fill_h(offset_in);
    denom = __msa_fill_h(log2_denom + 1);

    wgt = __msa_ilvev_b(dst_wgt, src_wgt);

    LD_UB8(src, stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += 8 * stride;
    LD_UB8(dst, stride, dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
    XORI_B8_128_UB(src0, src1, src2, src3, src4, src5, src6, src7);
    XORI_B8_128_UB(dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
    ILVR_B4_SB(dst0, src0, dst1, src1, dst2, src2, dst3, src3, vec0, vec2, vec4,
               vec6);
    ILVL_B4_SB(dst0, src0, dst1, src1, dst2, src2, dst3, src3, vec1, vec3, vec5,
               vec7);
    ILVR_B4_SB(dst4, src4, dst5, src5, dst6, src6, dst7, src7, vec8, vec10,
               vec12, vec14);
    ILVL_B4_SB(dst4, src4, dst5, src5, dst6, src6, dst7, src7, vec9, vec11,
               vec13, vec15);
    tmp0 = __msa_dpadd_s_h(offset, wgt, vec0);
    tmp1 = __msa_dpadd_s_h(offset, wgt, vec1);
    tmp2 = __msa_dpadd_s_h(offset, wgt, vec2);
    tmp3 = __msa_dpadd_s_h(offset, wgt, vec3);
    tmp4 = __msa_dpadd_s_h(offset, wgt, vec4);
    tmp5 = __msa_dpadd_s_h(offset, wgt, vec5);
    tmp6 = __msa_dpadd_s_h(offset, wgt, vec6);
    tmp7 = __msa_dpadd_s_h(offset, wgt, vec7);
    tmp8 = __msa_dpadd_s_h(offset, wgt, vec8);
    tmp9 = __msa_dpadd_s_h(offset, wgt, vec9);
    tmp10 = __msa_dpadd_s_h(offset, wgt, vec10);
    tmp11 = __msa_dpadd_s_h(offset, wgt, vec11);
    tmp12 = __msa_dpadd_s_h(offset, wgt, vec12);
    tmp13 = __msa_dpadd_s_h(offset, wgt, vec13);
    tmp14 = __msa_dpadd_s_h(offset, wgt, vec14);
    tmp15 = __msa_dpadd_s_h(offset, wgt, vec15);
    SRA_4V(tmp0, tmp1, tmp2, tmp3, denom);
    SRA_4V(tmp4, tmp5, tmp6, tmp7, denom);
    SRA_4V(tmp8, tmp9, tmp10, tmp11, denom);
    SRA_4V(tmp12, tmp13, tmp14, tmp15, denom);
    CLIP_SH8_0_255(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);
    CLIP_SH8_0_255(tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15);
    PCKEV_B4_UB(tmp1, tmp0, tmp3, tmp2, tmp5, tmp4, tmp7, tmp6, dst0, dst1,
                dst2, dst3);
    PCKEV_B4_UB(tmp9, tmp8, tmp11, tmp10, tmp13, tmp12, tmp15, tmp14, dst4,
                dst5, dst6, dst7);
    ST_UB8(dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst, stride);
    dst += 8 * stride;

    if (16 == height) {
        LD_UB8(src, stride, src0, src1, src2, src3, src4, src5, src6, src7);
        LD_UB8(dst, stride, dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
        XORI_B8_128_UB(src0, src1, src2, src3, src4, src5, src6, src7);
        XORI_B8_128_UB(dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
        ILVR_B4_SB(dst0, src0, dst1, src1, dst2, src2, dst3, src3, vec0, vec2,
                   vec4, vec6);
        ILVL_B4_SB(dst0, src0, dst1, src1, dst2, src2, dst3, src3, vec1, vec3,
                   vec5, vec7);
        ILVR_B4_SB(dst4, src4, dst5, src5, dst6, src6, dst7, src7, vec8, vec10,
                   vec12, vec14);
        ILVL_B4_SB(dst4, src4, dst5, src5, dst6, src6, dst7, src7, vec9, vec11,
                   vec13, vec15);
        tmp0 = __msa_dpadd_s_h(offset, wgt, vec0);
        tmp1 = __msa_dpadd_s_h(offset, wgt, vec1);
        tmp2 = __msa_dpadd_s_h(offset, wgt, vec2);
        tmp3 = __msa_dpadd_s_h(offset, wgt, vec3);
        tmp4 = __msa_dpadd_s_h(offset, wgt, vec4);
        tmp5 = __msa_dpadd_s_h(offset, wgt, vec5);
        tmp6 = __msa_dpadd_s_h(offset, wgt, vec6);
        tmp7 = __msa_dpadd_s_h(offset, wgt, vec7);
        tmp8 = __msa_dpadd_s_h(offset, wgt, vec8);
        tmp9 = __msa_dpadd_s_h(offset, wgt, vec9);
        tmp10 = __msa_dpadd_s_h(offset, wgt, vec10);
        tmp11 = __msa_dpadd_s_h(offset, wgt, vec11);
        tmp12 = __msa_dpadd_s_h(offset, wgt, vec12);
        tmp13 = __msa_dpadd_s_h(offset, wgt, vec13);
        tmp14 = __msa_dpadd_s_h(offset, wgt, vec14);
        tmp15 = __msa_dpadd_s_h(offset, wgt, vec15);
        SRA_4V(tmp0, tmp1, tmp2, tmp3, denom);
        SRA_4V(tmp4, tmp5, tmp6, tmp7, denom);
        SRA_4V(tmp8, tmp9, tmp10, tmp11, denom);
        SRA_4V(tmp12, tmp13, tmp14, tmp15, denom);
        CLIP_SH8_0_255(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7);
        CLIP_SH8_0_255(tmp8, tmp9, tmp10, tmp11, tmp12, tmp13, tmp14, tmp15);
        PCKEV_B4_UB(tmp1, tmp0, tmp3, tmp2, tmp5, tmp4, tmp7, tmp6, dst0, dst1,
                    dst2, dst3);
        PCKEV_B4_UB(tmp9, tmp8, tmp11, tmp10, tmp13, tmp12, tmp15, tmp14, dst4,
                    dst5, dst6, dst7);
        ST_UB8(dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst, stride);
    }
}