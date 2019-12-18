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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH8_0_255 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSERT_D2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD4 (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  XORI_B4_128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_dpadd_s_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_b (int) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_ilvev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void avc_biwgt_8x16_msa(uint8_t *src, uint8_t *dst, int32_t stride,
                               int32_t log2_denom, int32_t src_weight,
                               int32_t dst_weight, int32_t offset_in)
{
    uint8_t cnt;
    uint64_t tp0, tp1, tp2, tp3;
    v16i8 src_wgt, dst_wgt, wgt;
    v16u8 src0, src1, src2, src3;
    v16u8 dst0, dst1, dst2, dst3;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v8i16 temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7;
    v8i16 denom, offset;

    offset_in = (unsigned) ((offset_in + 1) | 1) << log2_denom;
    offset_in += (128 * (src_weight + dst_weight));

    src_wgt = __msa_fill_b(src_weight);
    dst_wgt = __msa_fill_b(dst_weight);
    offset = __msa_fill_h(offset_in);
    denom = __msa_fill_h(log2_denom + 1);
    wgt = __msa_ilvev_b(dst_wgt, src_wgt);

    for (cnt = 2; cnt--;) {
        LD4(src, stride, tp0, tp1, tp2, tp3);
        src += 4 * stride;
        INSERT_D2_UB(tp0, tp1, src0);
        INSERT_D2_UB(tp2, tp3, src1);
        LD4(src, stride, tp0, tp1, tp2, tp3);
        src += 4 * stride;
        INSERT_D2_UB(tp0, tp1, src2);
        INSERT_D2_UB(tp2, tp3, src3);
        LD4(dst, stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, dst0);
        INSERT_D2_UB(tp2, tp3, dst1);
        LD4(dst + 4 * stride, stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, dst2);
        INSERT_D2_UB(tp2, tp3, dst3);
        XORI_B4_128_UB(src0, src1, src2, src3);
        XORI_B4_128_UB(dst0, dst1, dst2, dst3);
        ILVR_B4_SB(dst0, src0, dst1, src1, dst2, src2, dst3, src3,
                   vec0, vec2, vec4, vec6);
        ILVL_B4_SB(dst0, src0, dst1, src1, dst2, src2, dst3, src3,
                   vec1, vec3, vec5, vec7);

        temp0 = __msa_dpadd_s_h(offset, wgt, vec0);
        temp1 = __msa_dpadd_s_h(offset, wgt, vec1);
        temp2 = __msa_dpadd_s_h(offset, wgt, vec2);
        temp3 = __msa_dpadd_s_h(offset, wgt, vec3);
        temp4 = __msa_dpadd_s_h(offset, wgt, vec4);
        temp5 = __msa_dpadd_s_h(offset, wgt, vec5);
        temp6 = __msa_dpadd_s_h(offset, wgt, vec6);
        temp7 = __msa_dpadd_s_h(offset, wgt, vec7);

        SRA_4V(temp0, temp1, temp2, temp3, denom);
        SRA_4V(temp4, temp5, temp6, temp7, denom);
        CLIP_SH8_0_255(temp0, temp1, temp2, temp3, temp4, temp5, temp6, temp7);
        PCKEV_B4_UB(temp1, temp0, temp3, temp2, temp5, temp4, temp7, temp6,
                    dst0, dst1, dst2, dst3);
        ST_D8(dst0, dst1, dst2, dst3, 0, 1, 0, 1, 0, 1, 0, 1, dst, stride);
        dst += 8 * stride;
    }
}