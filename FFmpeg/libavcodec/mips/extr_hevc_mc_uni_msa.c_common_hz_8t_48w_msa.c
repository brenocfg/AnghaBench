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
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_SB3_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPADD_SB2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 scalar_t__ LD_UB (int /*<<< orphan*/ *) ; 
 scalar_t__ PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH3_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_UB (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSHF_B3_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_dpadd_s_h (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_srari_h (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __msa_xori_b (scalar_t__,int) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void common_hz_8t_48w_msa(uint8_t *src, int32_t src_stride,
                                 uint8_t *dst, int32_t dst_stride,
                                 const int8_t *filter, int32_t height)
{
    uint32_t loop_cnt;
    v16i8 src0, src1, src2, src3, filt0, filt1, filt2, filt3, vec0, vec1, vec2;
    v16i8 src4;
    v16u8 mask0, mask1, mask2, mask3, mask4, mask5, mask6, mask7, out;
    v8i16 filt, out0, out1, out2, out3;

    mask0 = LD_UB(&ff_hevc_mask_arr[0]);
    src -= 3;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H4_SB(filt, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;
    mask4 = mask0 + 8;
    mask5 = mask0 + 10;
    mask6 = mask0 + 12;
    mask7 = mask0 + 14;

    for (loop_cnt = 64; loop_cnt--;) {
        src0 = LD_SB(src);
        src1 = LD_SB(src + 8);
        src2 = LD_SB(src + 16);
        src3 = LD_SB(src + 32);
        src4 = LD_SB(src + 40);
        src += src_stride;

        XORI_B4_128_SB(src0, src1, src2, src3);
        src4 = (v16i8) __msa_xori_b((v16u8) src4, 128);

        VSHF_B3_SB(src0, src0, src1, src1, src2, src2, mask0, mask0, mask0,
                   vec0, vec1, vec2);
        DOTP_SB3_SH(vec0, vec1, vec2, filt0, filt0, filt0, out0, out1, out2);
        VSHF_B3_SB(src0, src0, src1, src1, src2, src2, mask1, mask1, mask1,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt1, filt1, out0, out1);
        out2 = __msa_dpadd_s_h(out2, vec2, filt1);
        VSHF_B3_SB(src0, src0, src1, src1, src2, src2, mask2, mask2, mask2,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt2, filt2, out0, out1);
        out2 = __msa_dpadd_s_h(out2, vec2, filt2);

        VSHF_B3_SB(src0, src0, src1, src1, src2, src2, mask3, mask3, mask3,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt3, filt3, out0, out1);
        out2 = __msa_dpadd_s_h(out2, vec2, filt3);

        SRARI_H2_SH(out0, out1, 6);
        out3 = __msa_srari_h(out2, 6);
        SAT_SH3_SH(out0, out1, out3, 7);
        out = PCKEV_XORI128_UB(out0, out1);
        ST_UB(out, dst);

        VSHF_B3_SB(src2, src3, src3, src3, src4, src4, mask4, mask0, mask0,
                   vec0, vec1, vec2);
        DOTP_SB3_SH(vec0, vec1, vec2, filt0, filt0, filt0, out0, out1, out2);
        VSHF_B3_SB(src2, src3, src3, src3, src4, src4, mask5, mask1, mask1,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt1, filt1, out0, out1);
        out2 = __msa_dpadd_s_h(out2, vec2, filt1);
        VSHF_B3_SB(src2, src3, src3, src3, src4, src4, mask6, mask2, mask2,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt2, filt2, out0, out1);
        out2 = __msa_dpadd_s_h(out2, vec2, filt2);
        VSHF_B3_SB(src2, src3, src3, src3, src4, src4, mask7, mask3, mask3,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt3, filt3, out0, out1);
        out2 = __msa_dpadd_s_h(out2, vec2, filt3);

        SRARI_H2_SH(out0, out1, 6);
        out2 = __msa_srari_h(out2, 6);
        SAT_SH3_SH(out0, out1, out2, 7);
        out = PCKEV_XORI128_UB(out3, out0);
        ST_UB(out, dst + 16);
        out = PCKEV_XORI128_UB(out1, out2);
        ST_UB(out, dst + 32);
        dst += dst_stride;
    }
}