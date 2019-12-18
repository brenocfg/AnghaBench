#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ v8u16 ;
struct TYPE_36__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HADD_UB2_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HADD_UB3_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_UH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B3_UH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,scalar_t__,scalar_t__,scalar_t__) ; 
 TYPE_1__ LD_SB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/  const*,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SLDI_B2_SB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SLDI_B3_SB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SRA_4V (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_D4 (TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void common_hv_bil_no_rnd_4x8_msa(const uint8_t *src, int32_t src_stride,
                                         uint8_t *dst, int32_t dst_stride)
{
    v16i8 src0, src1, src2, src3, src4;
    v16i8 src0_sld1, src1_sld1, src2_sld1, src3_sld1, src4_sld1;
    v8u16 src0_r, src1_r, src2_r, src3_r, src4_r;
    v8u16 add0, add1, add2, add3, add4;
    v8u16 sum0, sum1, sum2, sum3;
    v16i8 out0, out1;
    v16i8 zeros = { 0 };

    LD_SB4(src, src_stride, src0, src1, src2, src3);
    src += (4 * src_stride);
    src4 = LD_SB(src);

    SLDI_B3_SB(zeros, src0, zeros, src1, zeros, src2, 1, src0_sld1,
               src1_sld1, src2_sld1);
    SLDI_B2_SB(zeros, src3, zeros, src4, 1, src3_sld1, src4_sld1);
    ILVR_B3_UH(src0_sld1, src0, src1_sld1, src1, src2_sld1, src2, src0_r,
               src1_r, src2_r);
    ILVR_B2_UH(src3_sld1, src3, src4_sld1, src4, src3_r, src4_r);
    HADD_UB3_UH(src0_r, src1_r, src2_r, add0, add1, add2);
    HADD_UB2_UH(src3_r, src4_r, add3, add4);

    sum0 = add0 + add1 + 1;
    sum1 = add1 + add2 + 1;
    sum2 = add2 + add3 + 1;
    sum3 = add3 + add4 + 1;

    SRA_4V(sum0, sum1, sum2, sum3, 2);
    PCKEV_B2_SB(sum1, sum0, sum3, sum2, out0, out1);
    ST_D4(out0, out1, 0, 1, 0, 1, dst, dst_stride);
}