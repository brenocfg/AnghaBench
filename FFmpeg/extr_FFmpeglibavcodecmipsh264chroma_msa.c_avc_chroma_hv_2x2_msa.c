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
typedef  scalar_t__ v8i16 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_UB2_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_UB3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SH (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSHF_B2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_copy_u_h (scalar_t__,int) ; 
 int /*<<< orphan*/  __msa_fill_b (int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_fill_h (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_ilvr_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_pckev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_sat_u_h (scalar_t__,int) ; 
 scalar_t__ __msa_srari_h (scalar_t__,int) ; 
 int /*<<< orphan*/ * chroma_mask_arr ; 

__attribute__((used)) static void avc_chroma_hv_2x2_msa(uint8_t *src, uint8_t *dst, int32_t stride,
                                  uint32_t coef_hor0, uint32_t coef_hor1,
                                  uint32_t coef_ver0, uint32_t coef_ver1)
{
    uint16_t out0, out1;
    v16u8 src0, src1, src2;
    v8u16 res_hz0, res_hz1, res_vt0, res_vt1;
    v8i16 res_vert;
    v16i8 mask;
    v16i8 coeff_hz_vec0 = __msa_fill_b(coef_hor0);
    v16i8 coeff_hz_vec1 = __msa_fill_b(coef_hor1);
    v16u8 coeff_hz_vec = (v16u8) __msa_ilvr_b(coeff_hz_vec0, coeff_hz_vec1);
    v8u16 coeff_vt_vec0 = (v8u16) __msa_fill_h(coef_ver0);
    v8u16 coeff_vt_vec1 = (v8u16) __msa_fill_h(coef_ver1);

    mask = LD_SB(&chroma_mask_arr[48]);

    LD_UB3(src, stride, src0, src1, src2);
    VSHF_B2_UB(src0, src1, src1, src2, mask, mask, src0, src1);
    DOTP_UB2_UH(src0, src1, coeff_hz_vec, coeff_hz_vec, res_hz0, res_hz1);
    MUL2(res_hz0, coeff_vt_vec1, res_hz1, coeff_vt_vec0, res_vt0, res_vt1);

    res_vt0 += res_vt1;
    res_vt0 = (v8u16) __msa_srari_h((v8i16) res_vt0, 6);
    res_vt0 = __msa_sat_u_h(res_vt0, 7);
    res_vert = (v8i16) __msa_pckev_b((v16i8) res_vt0, (v16i8) res_vt0);

    out0 = __msa_copy_u_h(res_vert, 0);
    out1 = __msa_copy_u_h(res_vert, 1);

    SH(out0, dst);
    dst += stride;
    SH(out1, dst);
}