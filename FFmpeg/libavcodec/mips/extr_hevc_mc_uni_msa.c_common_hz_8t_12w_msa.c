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
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_SB2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOTP_SB4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPADD_SB2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPADD_SB4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 scalar_t__ LD_UB (int /*<<< orphan*/ *) ; 
 scalar_t__ PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D4 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W4 (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void common_hz_8t_12w_msa(uint8_t *src, int32_t src_stride,
                                 uint8_t *dst, int32_t dst_stride,
                                 const int8_t *filter, int32_t height)
{
    uint32_t loop_cnt;
    v16u8 mask0, mask1, mask2, mask3, mask4, mask5, mask6, mask00;
    v16u8 tmp0, tmp1, tmp2;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 filt0, filt1, filt2, filt3;
    v8i16 filt, out0, out1, out2, out3, out4, out5;

    mask00 = LD_UB(&ff_hevc_mask_arr[0]);
    mask0 = LD_UB(&ff_hevc_mask_arr[16]);

    src = src - 3;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H4_SB(filt, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    mask1 = mask00 + 2;
    mask2 = mask00 + 4;
    mask3 = mask00 + 6;
    mask4 = mask0 + 2;
    mask5 = mask0 + 4;
    mask6 = mask0 + 6;

    for (loop_cnt = 4; loop_cnt--;) {
        /* 8 width */
        LD_SB4(src, src_stride, src0, src1, src2, src3);
        /* 4 width */
        LD_SB4(src + 8, src_stride, src4, src5, src6, src7);

        XORI_B4_128_SB(src0, src1, src2, src3);
        XORI_B4_128_SB(src4, src5, src6, src7);
        src += (4 * src_stride);

        VSHF_B2_SB(src0, src0, src1, src1, mask00, mask00, vec0, vec1);
        VSHF_B2_SB(src2, src2, src3, src3, mask00, mask00, vec2, vec3);
        DOTP_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0, out0,
                    out1, out2, out3);
        VSHF_B2_SB(src0, src0, src1, src1, mask2, mask2, vec0, vec1);
        VSHF_B2_SB(src2, src2, src3, src3, mask2, mask2, vec2, vec3);
        DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt2, filt2, filt2, filt2, out0,
                     out1, out2, out3);
        VSHF_B2_SB(src0, src0, src1, src1, mask1, mask1, vec4, vec5);
        VSHF_B2_SB(src2, src2, src3, src3, mask1, mask1, vec6, vec7);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt1, filt1, filt1, filt1, out0,
                     out1, out2, out3);
        VSHF_B2_SB(src0, src0, src1, src1, mask3, mask3, vec4, vec5);
        VSHF_B2_SB(src2, src2, src3, src3, mask3, mask3, vec6, vec7);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt3, filt3, filt3, filt3, out0,
                     out1, out2, out3);

        /* 4 width */
        VSHF_B2_SB(src4, src5, src6, src7, mask0, mask0, vec0, vec1);
        DOTP_SB2_SH(vec0, vec1, filt0, filt0, out4, out5);
        VSHF_B2_SB(src4, src5, src6, src7, mask4, mask4, vec2, vec3);
        DPADD_SB2_SH(vec2, vec3, filt1, filt1, out4, out5);
        VSHF_B2_SB(src4, src5, src6, src7, mask5, mask5, vec4, vec5);
        DPADD_SB2_SH(vec4, vec5, filt2, filt2, out4, out5);
        VSHF_B2_SB(src4, src5, src6, src7, mask6, mask6, vec6, vec7);
        DPADD_SB2_SH(vec6, vec7, filt3, filt3, out4, out5);

        SRARI_H4_SH(out0, out1, out2, out3, 6);
        SRARI_H2_SH(out4, out5, 6);
        SAT_SH4_SH(out0, out1, out2, out3, 7);
        SAT_SH2_SH(out4, out5, 7);
        tmp0 = PCKEV_XORI128_UB(out0, out1);
        tmp1 = PCKEV_XORI128_UB(out2, out3);
        tmp2 = PCKEV_XORI128_UB(out4, out5);

        ST_D4(tmp0, tmp1, 0, 1, 0, 1, dst, dst_stride);
        ST_W4(tmp2, 0, 1, 2, 3, dst + 8, dst_stride);
        dst += (4 * dst_stride);
    }
}