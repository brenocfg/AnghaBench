#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_120__   TYPE_1__ ;

/* Type definitions */
struct TYPE_120__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUTTERFLY_4 (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  BUTTERFLY_8 (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  DOTP_SH2_SW (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DOTP_SH4_SW (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_H2_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ILVR_D2_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ILVR_H2_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  LD_SH8 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  PCKEV_H2_SH (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int) ; 
 int /*<<< orphan*/  SRARI_W2_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_W4_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_SH8 (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE4X8_SH_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VP9_ADDBLK_ST8x4_UB (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VP9_DCT_CONST_BITS ; 
 int /*<<< orphan*/  VP9_IDCT8x8_1D (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 TYPE_1__ VP9_SET_COSPI_PAIR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ __msa_ilvr_h (TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  cospi_12_64 ; 
 int /*<<< orphan*/  cospi_16_64 ; 
 int /*<<< orphan*/  cospi_20_64 ; 
 int /*<<< orphan*/  cospi_24_64 ; 
 int /*<<< orphan*/  cospi_28_64 ; 
 int /*<<< orphan*/  cospi_4_64 ; 
 int /*<<< orphan*/  cospi_8_64 ; 

__attribute__((used)) static void vp9_idct8x8_12_colcol_addblk_msa(int16_t *input, uint8_t *dst,
                                             int32_t dst_stride)
{
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v8i16 s0, s1, s2, s3, s4, s5, s6, s7, k0, k1, k2, k3, m0, m1, m2, m3;
    v4i32 tmp0, tmp1, tmp2, tmp3;
    v8i16 zero = { 0 };

    /* load vector elements of 8x8 block */
    LD_SH8(input, 8, in0, in1, in2, in3, in4, in5, in6, in7);
    ST_SH8(zero, zero, zero, zero, zero, zero, zero, zero, input, 8);
    ILVR_D2_SH(in1, in0, in3, in2, in0, in1);
    ILVR_D2_SH(in5, in4, in7, in6, in2, in3);

    /* stage1 */
    ILVL_H2_SH(in3, in0, in2, in1, s0, s1);
    k0 = VP9_SET_COSPI_PAIR(cospi_28_64, -cospi_4_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_4_64, cospi_28_64);
    k2 = VP9_SET_COSPI_PAIR(-cospi_20_64, cospi_12_64);
    k3 = VP9_SET_COSPI_PAIR(cospi_12_64, cospi_20_64);
    DOTP_SH4_SW(s0, s0, s1, s1, k0, k1, k2, k3, tmp0, tmp1, tmp2, tmp3);
    SRARI_W4_SW(tmp0, tmp1, tmp2, tmp3, VP9_DCT_CONST_BITS);
    PCKEV_H2_SH(zero, tmp0, zero, tmp1, s0, s1);
    PCKEV_H2_SH(zero, tmp2, zero, tmp3, s2, s3);
    BUTTERFLY_4(s0, s1, s3, s2, s4, s7, s6, s5);

    /* stage2 */
    ILVR_H2_SH(in3, in1, in2, in0, s1, s0);
    k0 = VP9_SET_COSPI_PAIR(cospi_16_64, cospi_16_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_16_64, -cospi_16_64);
    k2 = VP9_SET_COSPI_PAIR(cospi_24_64, -cospi_8_64);
    k3 = VP9_SET_COSPI_PAIR(cospi_8_64, cospi_24_64);
    DOTP_SH4_SW(s0, s0, s1, s1, k0, k1, k2, k3, tmp0, tmp1, tmp2, tmp3);
    SRARI_W4_SW(tmp0, tmp1, tmp2, tmp3, VP9_DCT_CONST_BITS);
    PCKEV_H2_SH(zero, tmp0, zero, tmp1, s0, s1);
    PCKEV_H2_SH(zero, tmp2, zero, tmp3, s2, s3);
    BUTTERFLY_4(s0, s1, s2, s3, m0, m1, m2, m3);

    /* stage3 */
    s0 = __msa_ilvr_h(s6, s5);

    k1 = VP9_SET_COSPI_PAIR(-cospi_16_64, cospi_16_64);
    DOTP_SH2_SW(s0, s0, k1, k0, tmp0, tmp1);
    SRARI_W2_SW(tmp0, tmp1, VP9_DCT_CONST_BITS);
    PCKEV_H2_SH(zero, tmp0, zero, tmp1, s2, s3);

    /* stage4 */
    BUTTERFLY_8(m0, m1, m2, m3, s4, s2, s3, s7,
                in0, in1, in2, in3, in4, in5, in6, in7);
    TRANSPOSE4X8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                       in0, in1, in2, in3, in4, in5, in6, in7);
    VP9_IDCT8x8_1D(in0, in1, in2, in3, in4, in5, in6, in7,
                   in0, in1, in2, in3, in4, in5, in6, in7);

    /* final rounding (add 2^4, divide by 2^5) and shift */
    SRARI_H4_SH(in0, in1, in2, in3, 5);
    SRARI_H4_SH(in4, in5, in6, in7, 5);

    /* add block and store 8x8 */
    VP9_ADDBLK_ST8x4_UB(dst, dst_stride, in0, in1, in2, in3);
    dst += (4 * dst_stride);
    VP9_ADDBLK_ST8x4_UB(dst, dst_stride, in4, in5, in6, in7);
}