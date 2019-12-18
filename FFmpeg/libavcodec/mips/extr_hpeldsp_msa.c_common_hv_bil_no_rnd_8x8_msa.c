#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ v8u16 ;
typedef  int /*<<< orphan*/  v16u8 ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HADD_UB3_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B3_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B4_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SLDI_B2_UB (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLDI_B3_UB (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLDI_B4_UB (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRA_4V (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_D4 (TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void common_hv_bil_no_rnd_8x8_msa(const uint8_t *src, int32_t src_stride,
                                         uint8_t *dst, int32_t dst_stride)
{
    v16u8 src0, src1, src2, src3, src4, src5, src6, src7, src8;
    v16u8 src0_sld1, src1_sld1, src2_sld1, src3_sld1;
    v16u8 src4_sld1, src5_sld1, src6_sld1, src7_sld1, src8_sld1;
    v8u16 src0_r, src1_r, src2_r, src3_r;
    v8u16 src4_r, src5_r, src6_r, src7_r, src8_r;
    v8u16 add0, add1, add2, add3, add4, add5, add6, add7, add8;
    v8u16 sum0, sum1, sum2, sum3, sum4, sum5, sum6, sum7;
    v16i8 out0, out1;
    v16i8 zeros = { 0 };

    LD_UB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += (8 * src_stride);
    src8 = LD_UB(src);

    SLDI_B4_UB(zeros, src0, zeros, src1, zeros, src2, zeros, src3, 1,
               src0_sld1, src1_sld1, src2_sld1, src3_sld1);
    SLDI_B3_UB(zeros, src4, zeros, src5, zeros, src6, 1, src4_sld1,
               src5_sld1, src6_sld1);
    SLDI_B2_UB(zeros, src7, zeros, src8, 1, src7_sld1, src8_sld1);
    ILVR_B4_UH(src0_sld1, src0, src1_sld1, src1, src2_sld1, src2, src3_sld1,
               src3, src0_r, src1_r, src2_r, src3_r);
    ILVR_B3_UH(src4_sld1, src4, src5_sld1, src5, src6_sld1, src6, src4_r,
               src5_r, src6_r);
    ILVR_B2_UH(src7_sld1, src7, src8_sld1, src8, src7_r, src8_r);
    HADD_UB3_UH(src0_r, src1_r, src2_r, add0, add1, add2);
    HADD_UB3_UH(src3_r, src4_r, src5_r, add3, add4, add5);
    HADD_UB3_UH(src6_r, src7_r, src8_r, add6, add7, add8);

    sum0 = add0 + add1 + 1;
    sum1 = add1 + add2 + 1;
    sum2 = add2 + add3 + 1;
    sum3 = add3 + add4 + 1;
    sum4 = add4 + add5 + 1;
    sum5 = add5 + add6 + 1;
    sum6 = add6 + add7 + 1;
    sum7 = add7 + add8 + 1;

    SRA_4V(sum0, sum1, sum2, sum3, 2);
    SRA_4V(sum4, sum5, sum6, sum7, 2);
    PCKEV_B2_SB(sum1, sum0, sum3, sum2, out0, out1);
    ST_D4(out0, out1, 0, 1, 0, 1, dst, dst_stride);
    PCKEV_B2_SB(sum5, sum4, sum7, sum6, out0, out1);
    ST_D4(out0, out1, 0, 1, 0, 1, dst + 4 * dst_stride, dst_stride);
}