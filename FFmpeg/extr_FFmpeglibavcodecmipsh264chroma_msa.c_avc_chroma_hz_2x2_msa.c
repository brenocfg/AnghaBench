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
typedef  int v8u16 ;
typedef  scalar_t__ v8i16 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SH (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __msa_copy_u_h (scalar_t__,int) ; 
 int __msa_dotp_u_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_fill_b (int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_ilvr_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 int __msa_sat_u_h (int,int) ; 
 scalar_t__ __msa_srari_h (scalar_t__,int) ; 
 scalar_t__ __msa_vshf_b (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * chroma_mask_arr ; 

__attribute__((used)) static void avc_chroma_hz_2x2_msa(uint8_t *src, uint8_t *dst, int32_t stride,
                                  uint32_t coeff0, uint32_t coeff1)
{
    uint16_t out0, out1;
    v16i8 src0, src1;
    v8u16 res_r;
    v8i16 res;
    v16i8 mask;
    v16i8 coeff_vec0 = __msa_fill_b(coeff0);
    v16i8 coeff_vec1 = __msa_fill_b(coeff1);
    v16u8 coeff_vec = (v16u8) __msa_ilvr_b(coeff_vec0, coeff_vec1);

    mask = LD_SB(&chroma_mask_arr[0]);

    LD_SB2(src, stride, src0, src1);

    src0 = __msa_vshf_b(mask, src1, src0);
    res_r = __msa_dotp_u_h((v16u8) src0, coeff_vec);
    res_r <<= 3;
    res_r = (v8u16) __msa_srari_h((v8i16) res_r, 6);
    res_r = __msa_sat_u_h(res_r, 7);
    res = (v8i16) __msa_pckev_b((v16i8) res_r, (v16i8) res_r);

    out0 = __msa_copy_u_h(res, 0);
    out1 = __msa_copy_u_h(res, 2);

    SH(out0, dst);
    dst += stride;
    SH(out1, dst);
}