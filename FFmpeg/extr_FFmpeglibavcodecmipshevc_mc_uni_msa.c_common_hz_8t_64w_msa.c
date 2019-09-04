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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_SB4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPADD_SB4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 scalar_t__ LD_UB (int /*<<< orphan*/ *) ; 
 scalar_t__ PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_UB (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSHF_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void common_hz_8t_64w_msa(uint8_t *src, int32_t src_stride,
                                 uint8_t *dst, int32_t dst_stride,
                                 const int8_t *filter, int32_t height)
{
    int32_t loop_cnt;
    v16u8 mask0, mask1, mask2, mask3, out;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 filt0, filt1, filt2, filt3;
    v8i16 res0, res1, res2, res3, filt;

    mask0 = LD_UB(&ff_hevc_mask_arr[0]);
    src -= 3;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H4_SB(filt, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;

    for (loop_cnt = height; loop_cnt--;) {
        LD_SB8(src, 8, src0, src1, src2, src3, src4, src5, src6, src7);
        src += src_stride;

        XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);

        VSHF_B2_SB(src0, src0, src1, src1, mask0, mask0, vec0, vec1);
        VSHF_B2_SB(src2, src2, src3, src3, mask0, mask0, vec2, vec3);
        DOTP_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0, res0,
                    res1, res2, res3);
        VSHF_B2_SB(src0, src0, src1, src1, mask2, mask2, vec0, vec1);
        VSHF_B2_SB(src2, src2, src3, src3, mask2, mask2, vec2, vec3);
        DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt2, filt2, filt2, filt2, res0,
                     res1, res2, res3);
        VSHF_B2_SB(src0, src0, src1, src1, mask1, mask1, vec4, vec5);
        VSHF_B2_SB(src2, src2, src3, src3, mask1, mask1, vec6, vec7);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt1, filt1, filt1, filt1, res0,
                     res1, res2, res3);
        VSHF_B2_SB(src0, src0, src1, src1, mask3, mask3, vec4, vec5);
        VSHF_B2_SB(src2, src2, src3, src3, mask3, mask3, vec6, vec7);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt3, filt3, filt3, filt3, res0,
                     res1, res2, res3);

        SRARI_H4_SH(res0, res1, res2, res3, 6);
        SAT_SH4_SH(res0, res1, res2, res3, 7);
        out = PCKEV_XORI128_UB(res0, res1);
        ST_UB(out, dst);
        out = PCKEV_XORI128_UB(res2, res3);
        ST_UB(out, dst + 16);

        VSHF_B2_SB(src4, src4, src5, src5, mask0, mask0, vec0, vec1);
        VSHF_B2_SB(src6, src6, src7, src7, mask0, mask0, vec2, vec3);
        DOTP_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0, res0,
                    res1, res2, res3);
        VSHF_B2_SB(src4, src4, src5, src5, mask2, mask2, vec0, vec1);
        VSHF_B2_SB(src6, src6, src7, src7, mask2, mask2, vec2, vec3);
        DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt2, filt2, filt2, filt2, res0,
                     res1, res2, res3);
        VSHF_B2_SB(src4, src4, src5, src5, mask1, mask1, vec4, vec5);
        VSHF_B2_SB(src6, src6, src7, src7, mask1, mask1, vec6, vec7);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt1, filt1, filt1, filt1, res0,
                     res1, res2, res3);
        VSHF_B2_SB(src4, src4, src5, src5, mask3, mask3, vec4, vec5);
        VSHF_B2_SB(src6, src6, src7, src7, mask3, mask3, vec6, vec7);
        DPADD_SB4_SH(vec4, vec5, vec6, vec7, filt3, filt3, filt3, filt3, res0,
                     res1, res2, res3);

        SRARI_H4_SH(res0, res1, res2, res3, 6);
        SAT_SH4_SH(res0, res1, res2, res3, 7);
        out = PCKEV_XORI128_UB(res0, res1);
        ST_UB(out, dst + 32);
        out = PCKEV_XORI128_UB(res2, res3);
        ST_UB(out, dst + 48);
        dst += dst_stride;
    }
}