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
typedef  int v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPADD_SB2_SH (scalar_t__,scalar_t__,int,int,int,int) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SW (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_copy_u_w (int /*<<< orphan*/ ,int) ; 
 int __msa_ldi_h (int) ; 
 int /*<<< orphan*/  ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_4t_6w_msa(uint8_t *src,
                              int32_t src_stride,
                              int16_t *dst,
                              int32_t dst_stride,
                              const int8_t *filter,
                              int32_t height)
{
    uint32_t loop_cnt;
    uint64_t dst_val0, dst_val1, dst_val2, dst_val3;
    uint32_t dst_val_int0, dst_val_int1, dst_val_int2, dst_val_int3;
    v8i16 filt0, filt1, dst0, dst1, dst2, dst3;
    v16i8 src0, src1, src2, src3;
    v16i8 mask0 = LD_SB(ff_hevc_mask_arr);
    v16i8 mask1;
    v16i8 vec0, vec1;
    v8i16 filter_vec, const_vec;

    src -= 1;

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    mask1 = mask0 + 2;

    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    for (loop_cnt = 2; loop_cnt--;) {
        LD_SB4(src, src_stride, src0, src1, src2, src3);
        src += (4 * src_stride);

        XORI_B4_128_SB(src0, src1, src2, src3);

        VSHF_B2_SB(src0, src0, src0, src0, mask0, mask1, vec0, vec1);
        dst0 = const_vec;
        DPADD_SB2_SH(vec0, vec1, filt0, filt1, dst0, dst0);
        VSHF_B2_SB(src1, src1, src1, src1, mask0, mask1, vec0, vec1);
        dst1 = const_vec;
        DPADD_SB2_SH(vec0, vec1, filt0, filt1, dst1, dst1);
        VSHF_B2_SB(src2, src2, src2, src2, mask0, mask1, vec0, vec1);
        dst2 = const_vec;
        DPADD_SB2_SH(vec0, vec1, filt0, filt1, dst2, dst2);
        VSHF_B2_SB(src3, src3, src3, src3, mask0, mask1, vec0, vec1);
        dst3 = const_vec;
        DPADD_SB2_SH(vec0, vec1, filt0, filt1, dst3, dst3);

        dst_val0 = __msa_copy_u_d((v2i64) dst0, 0);
        dst_val1 = __msa_copy_u_d((v2i64) dst1, 0);
        dst_val2 = __msa_copy_u_d((v2i64) dst2, 0);
        dst_val3 = __msa_copy_u_d((v2i64) dst3, 0);

        dst_val_int0 = __msa_copy_u_w((v4i32) dst0, 2);
        dst_val_int1 = __msa_copy_u_w((v4i32) dst1, 2);
        dst_val_int2 = __msa_copy_u_w((v4i32) dst2, 2);
        dst_val_int3 = __msa_copy_u_w((v4i32) dst3, 2);

        SD(dst_val0, dst);
        SW(dst_val_int0, dst + 4);
        dst += dst_stride;
        SD(dst_val1, dst);
        SW(dst_val_int1, dst + 4);
        dst += dst_stride;
        SD(dst_val2, dst);
        SW(dst_val_int2, dst + 4);
        dst += dst_stride;
        SD(dst_val3, dst);
        SW(dst_val_int3, dst + 4);
        dst += dst_stride;
    }
}