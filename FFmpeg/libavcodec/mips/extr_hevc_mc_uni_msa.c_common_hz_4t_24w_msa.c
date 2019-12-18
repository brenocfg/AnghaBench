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
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_SB4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPADD_SB4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void common_hz_4t_24w_msa(uint8_t *src, int32_t src_stride,
                                 uint8_t *dst, int32_t dst_stride,
                                 const int8_t *filter, int32_t height)
{
    uint8_t *dst1 = dst + 16;
    uint32_t loop_cnt;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 filt0, filt1, mask0, mask1, mask00, mask11;
    v8i16 filt, out0, out1, out2, out3;
    v16u8 tmp0, tmp1;

    mask0 = LD_SB(&ff_hevc_mask_arr[0]);
    src -= 1;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H2_SB(filt, 0, 1, filt0, filt1);

    mask1 = mask0 + 2;
    mask00 = mask0 + 8;
    mask11 = mask0 + 10;

    for (loop_cnt = 8; loop_cnt--;) {
        LD_SB4(src, src_stride, src0, src2, src4, src6);
        LD_SB4(src + 16, src_stride, src1, src3, src5, src7);
        src += (4 * src_stride);

        XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);
        VSHF_B2_SB(src0, src0, src0, src1, mask0, mask00, vec0, vec1);
        VSHF_B2_SB(src2, src2, src2, src3, mask0, mask00, vec2, vec3);
        VSHF_B2_SB(src0, src0, src0, src1, mask1, mask11, vec4, vec5);
        VSHF_B2_SB(src2, src2, src2, src3, mask1, mask11, vec6, vec7);
        DOTP_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                    out0, out1, out2, out3);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt1, filt1, filt1, filt1,
                     out0, out1, out2, out3);
        SRARI_H4_SH(out0, out1, out2, out3, 6);
        SAT_SH4_SH(out0, out1, out2, out3, 7);
        tmp0 = PCKEV_XORI128_UB(out0, out1);
        ST_UB(tmp0, dst);
        dst += dst_stride;
        tmp0 = PCKEV_XORI128_UB(out2, out3);
        ST_UB(tmp0, dst);
        dst += dst_stride;

        VSHF_B2_SB(src4, src4, src4, src5, mask0, mask00, vec0, vec1);
        VSHF_B2_SB(src6, src6, src6, src7, mask0, mask00, vec2, vec3);
        VSHF_B2_SB(src4, src4, src4, src5, mask1, mask11, vec4, vec5);
        VSHF_B2_SB(src6, src6, src6, src7, mask1, mask11, vec6, vec7);
        DOTP_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                    out0, out1, out2, out3);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt1, filt1, filt1, filt1,
                     out0, out1, out2, out3);
        SRARI_H4_SH(out0, out1, out2, out3, 6);
        SAT_SH4_SH(out0, out1, out2, out3, 7);
        tmp0 = PCKEV_XORI128_UB(out0, out1);
        ST_UB(tmp0, dst);
        dst += dst_stride;
        tmp0 = PCKEV_XORI128_UB(out2, out3);
        ST_UB(tmp0, dst);
        dst += dst_stride;

        /* 8 width */
        VSHF_B2_SB(src1, src1, src3, src3, mask0, mask0, vec0, vec1);
        VSHF_B2_SB(src5, src5, src7, src7, mask0, mask0, vec2, vec3);
        VSHF_B2_SB(src1, src1, src3, src3, mask1, mask1, vec4, vec5);
        VSHF_B2_SB(src5, src5, src7, src7, mask1, mask1, vec6, vec7);

        DOTP_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                    out0, out1, out2, out3);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt1, filt1, filt1, filt1,
                     out0, out1, out2, out3);

        SRARI_H4_SH(out0, out1, out2, out3, 6);
        SAT_SH4_SH(out0, out1, out2, out3, 7);
        tmp0 = PCKEV_XORI128_UB(out0, out1);
        tmp1 = PCKEV_XORI128_UB(out2, out3);
        ST_D4(tmp0, tmp1, 0, 1, 0, 1, dst1, dst_stride);
        dst1 += (4 * dst_stride);
    }
}