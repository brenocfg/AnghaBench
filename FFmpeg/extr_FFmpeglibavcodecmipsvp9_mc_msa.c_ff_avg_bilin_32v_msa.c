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
typedef  int /*<<< orphan*/  v8i16 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  const uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_UB2_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_B2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB2 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB4 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_UH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_AVG_ST_UB (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SAT_UH2_UH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SRARI_H2_UH (scalar_t__,scalar_t__,int) ; 
 scalar_t__ __msa_splati_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** vp9_bilinear_filters_msa ; 

void ff_avg_bilin_32v_msa(uint8_t *dst, ptrdiff_t dst_stride,
                          const uint8_t *src, ptrdiff_t src_stride,
                          int height, int mx, int my)
{
    uint32_t loop_cnt;
    const int8_t *filter = vp9_bilinear_filters_msa[my - 1];
    v16u8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9;
    v16u8 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v16u8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7, filt0;
    v8u16 tmp0, tmp1, tmp2, tmp3, filt;

    /* rearranging filter_y */
    filt = LD_UH(filter);
    filt0 = (v16u8) __msa_splati_h((v8i16) filt, 0);

    LD_UB2(src, 16, src0, src5);
    src += src_stride;

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_UB4(src, src_stride, src1, src2, src3, src4);
        LD_UB4(dst, dst_stride, dst0, dst1, dst2, dst3);
        ILVR_B2_UB(src1, src0, src2, src1, vec0, vec2);
        ILVL_B2_UB(src1, src0, src2, src1, vec1, vec3);

        LD_UB4(src + 16, src_stride, src6, src7, src8, src9);
        LD_UB4(dst + 16, dst_stride, dst4, dst5, dst6, dst7);
        src += (4 * src_stride);

        DOTP_UB2_UH(vec0, vec1, filt0, filt0, tmp0, tmp1);
        SRARI_H2_UH(tmp0, tmp1, 7);
        SAT_UH2_UH(tmp0, tmp1, 7);
        PCKEV_AVG_ST_UB(tmp1, tmp0, dst0, dst);

        DOTP_UB2_UH(vec2, vec3, filt0, filt0, tmp2, tmp3);
        SRARI_H2_UH(tmp2, tmp3, 7);
        SAT_UH2_UH(tmp2, tmp3, 7);
        PCKEV_AVG_ST_UB(tmp3, tmp2, dst1, dst + dst_stride);

        ILVR_B2_UB(src3, src2, src4, src3, vec4, vec6);
        ILVL_B2_UB(src3, src2, src4, src3, vec5, vec7);
        DOTP_UB2_UH(vec4, vec5, filt0, filt0, tmp0, tmp1);
        SRARI_H2_UH(tmp0, tmp1, 7);
        SAT_UH2_UH(tmp0, tmp1, 7);
        PCKEV_AVG_ST_UB(tmp1, tmp0, dst2, dst + 2 * dst_stride);

        DOTP_UB2_UH(vec6, vec7, filt0, filt0, tmp2, tmp3);
        SRARI_H2_UH(tmp2, tmp3, 7);
        SAT_UH2_UH(tmp2, tmp3, 7);
        PCKEV_AVG_ST_UB(tmp3, tmp2, dst3, dst + 3 * dst_stride);

        ILVR_B2_UB(src6, src5, src7, src6, vec0, vec2);
        ILVL_B2_UB(src6, src5, src7, src6, vec1, vec3);
        DOTP_UB2_UH(vec0, vec1, filt0, filt0, tmp0, tmp1);
        SRARI_H2_UH(tmp0, tmp1, 7);
        SAT_UH2_UH(tmp0, tmp1, 7);
        PCKEV_AVG_ST_UB(tmp1, tmp0, dst4, dst + 16);

        DOTP_UB2_UH(vec2, vec3, filt0, filt0, tmp2, tmp3);
        SRARI_H2_UH(tmp2, tmp3, 7);
        SAT_UH2_UH(tmp2, tmp3, 7);
        PCKEV_AVG_ST_UB(tmp3, tmp2, dst5, dst + 16 + dst_stride);

        ILVR_B2_UB(src8, src7, src9, src8, vec4, vec6);
        ILVL_B2_UB(src8, src7, src9, src8, vec5, vec7);
        DOTP_UB2_UH(vec4, vec5, filt0, filt0, tmp0, tmp1);
        SRARI_H2_UH(tmp0, tmp1, 7);
        SAT_UH2_UH(tmp0, tmp1, 7);
        PCKEV_AVG_ST_UB(tmp1, tmp0, dst6, dst + 16 + 2 * dst_stride);

        DOTP_UB2_UH(vec6, vec7, filt0, filt0, tmp2, tmp3);
        SRARI_H2_UH(tmp2, tmp3, 7);
        SAT_UH2_UH(tmp2, tmp3, 7);
        PCKEV_AVG_ST_UB(tmp3, tmp2, dst7, dst + 16 + 3 * dst_stride);
        dst += (4 * dst_stride);

        src0 = src4;
        src5 = src9;
    }
}