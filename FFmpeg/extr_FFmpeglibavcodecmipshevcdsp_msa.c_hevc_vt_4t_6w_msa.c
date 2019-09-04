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
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPADD_SB2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_copy_u_w (int /*<<< orphan*/ ,int) ; 
 int __msa_ldi_h (int) ; 

__attribute__((used)) static void hevc_vt_4t_6w_msa(uint8_t *src,
                              int32_t src_stride,
                              int16_t *dst,
                              int32_t dst_stride,
                              const int8_t *filter,
                              int32_t height)
{
    int32_t loop_cnt;
    uint32_t dst_val_int0, dst_val_int1, dst_val_int2, dst_val_int3;
    uint64_t dst_val0, dst_val1, dst_val2, dst_val3;
    v16i8 src0, src1, src2, src3, src4;
    v16i8 src10_r, src32_r, src21_r, src43_r;
    v8i16 dst0_r, dst1_r, dst2_r, dst3_r;
    v8i16 filt0, filt1;
    v8i16 filter_vec, const_vec;

    src -= src_stride;
    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    LD_SB3(src, src_stride, src0, src1, src2);
    src += (3 * src_stride);
    XORI_B3_128_SB(src0, src1, src2);
    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB2(src, src_stride, src3, src4);
        src += (2 * src_stride);
        XORI_B2_128_SB(src3, src4);
        ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);

        dst0_r = const_vec;
        DPADD_SB2_SH(src10_r, src32_r, filt0, filt1, dst0_r, dst0_r);
        dst1_r = const_vec;
        DPADD_SB2_SH(src21_r, src43_r, filt0, filt1, dst1_r, dst1_r);

        LD_SB2(src, src_stride, src1, src2);
        src += (2 * src_stride);
        XORI_B2_128_SB(src1, src2);
        ILVR_B2_SB(src1, src4, src2, src1, src10_r, src21_r);

        dst2_r = const_vec;
        DPADD_SB2_SH(src32_r, src10_r, filt0, filt1, dst2_r, dst2_r);
        dst3_r = const_vec;
        DPADD_SB2_SH(src43_r, src21_r, filt0, filt1, dst3_r, dst3_r);

        dst_val0 = __msa_copy_u_d((v2i64) dst0_r, 0);
        dst_val1 = __msa_copy_u_d((v2i64) dst1_r, 0);
        dst_val2 = __msa_copy_u_d((v2i64) dst2_r, 0);
        dst_val3 = __msa_copy_u_d((v2i64) dst3_r, 0);

        dst_val_int0 = __msa_copy_u_w((v4i32) dst0_r, 2);
        dst_val_int1 = __msa_copy_u_w((v4i32) dst1_r, 2);
        dst_val_int2 = __msa_copy_u_w((v4i32) dst2_r, 2);
        dst_val_int3 = __msa_copy_u_w((v4i32) dst3_r, 2);

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