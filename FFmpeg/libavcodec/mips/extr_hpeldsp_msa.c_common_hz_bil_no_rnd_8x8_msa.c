#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
struct TYPE_30__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVE_ST8x4_UB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/  const*,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SLDI_B4_SB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void common_hz_bil_no_rnd_8x8_msa(const uint8_t *src, int32_t src_stride,
                                         uint8_t *dst, int32_t dst_stride)
{
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 src0_sld1, src1_sld1, src2_sld1, src3_sld1;
    v16i8 src4_sld1, src5_sld1, src6_sld1, src7_sld1;
    v16i8 zeros = { 0 };

    LD_SB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += (8 * src_stride);

    SLDI_B4_SB(zeros, src0, zeros, src1, zeros, src2, zeros, src3, 1,
               src0_sld1, src1_sld1, src2_sld1, src3_sld1);
    SLDI_B4_SB(zeros, src4, zeros, src5, zeros, src6, zeros, src7, 1,
               src4_sld1, src5_sld1, src6_sld1, src7_sld1);

    AVE_ST8x4_UB(src0, src0_sld1, src1, src1_sld1,
                 src2, src2_sld1, src3, src3_sld1, dst, dst_stride);
    dst += (4 * dst_stride);
    AVE_ST8x4_UB(src4, src4_sld1, src5, src5_sld1,
                 src6, src6_sld1, src7, src7_sld1, dst, dst_stride);
}