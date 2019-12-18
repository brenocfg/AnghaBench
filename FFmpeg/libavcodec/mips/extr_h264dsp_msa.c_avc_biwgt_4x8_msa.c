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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH4_0_255 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSERT_W4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_W8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_dpadd_s_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_b (int) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_ilvev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void avc_biwgt_4x8_msa(uint8_t *src, uint8_t *dst, int32_t stride,
                              int32_t log2_denom, int32_t src_weight,
                              int32_t dst_weight, int32_t offset_in)
{
    uint32_t tp0, tp1, tp2, tp3;
    v16i8 src_wgt, dst_wgt, wgt, vec0, vec1, vec2, vec3;
    v16u8 src0, src1, dst0, dst1;
    v8i16 tmp0, tmp1, tmp2, tmp3, denom, offset;

    offset_in = (unsigned) ((offset_in + 1) | 1) << log2_denom;
    offset_in += (128 * (src_weight + dst_weight));

    src_wgt = __msa_fill_b(src_weight);
    dst_wgt = __msa_fill_b(dst_weight);
    offset = __msa_fill_h(offset_in);
    denom = __msa_fill_h(log2_denom + 1);
    wgt = __msa_ilvev_b(dst_wgt, src_wgt);

    LW4(src, stride, tp0, tp1, tp2, tp3);
    src += 4 * stride;
    INSERT_W4_UB(tp0, tp1, tp2, tp3, src0);
    LW4(src, stride, tp0, tp1, tp2, tp3);
    INSERT_W4_UB(tp0, tp1, tp2, tp3, src1);
    LW4(dst, stride, tp0, tp1, tp2, tp3);
    INSERT_W4_UB(tp0, tp1, tp2, tp3, dst0);
    LW4(dst + 4 * stride, stride, tp0, tp1, tp2, tp3);
    INSERT_W4_UB(tp0, tp1, tp2, tp3, dst1);
    XORI_B4_128_UB(src0, src1, dst0, dst1);
    ILVRL_B2_SB(dst0, src0, vec0, vec1);
    ILVRL_B2_SB(dst1, src1, vec2, vec3);
    tmp0 = __msa_dpadd_s_h(offset, wgt, vec0);
    tmp1 = __msa_dpadd_s_h(offset, wgt, vec1);
    tmp2 = __msa_dpadd_s_h(offset, wgt, vec2);
    tmp3 = __msa_dpadd_s_h(offset, wgt, vec3);
    SRA_4V(tmp0, tmp1, tmp2, tmp3, denom);
    CLIP_SH4_0_255(tmp0, tmp1, tmp2, tmp3);
    PCKEV_B2_UB(tmp1, tmp0, tmp3, tmp2, dst0, dst1);
    ST_W8(dst0, dst1, 0, 1, 2, 3, 0, 1, 2, 3, dst, stride);
}