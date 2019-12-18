#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  unsigned int uint32_t ;
typedef  unsigned int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDS_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSERT_D2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAXI_SH8_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUL4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SAT_UH8_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRLR_H8_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D8 (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  UNPCK_UB_SH (TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_h (unsigned int) ; 

__attribute__((used)) static void avc_wgt_8x16_msa(uint8_t *data, int32_t stride, int32_t log2_denom,
                             int32_t src_weight, int32_t offset_in)
{
    uint32_t offset_val, cnt;
    uint64_t tp0, tp1, tp2, tp3;
    v16u8 src0 = { 0 }, src1 = { 0 }, src2 = { 0 }, src3 = { 0 };
    v8i16 src0_r, src1_r, src2_r, src3_r, src4_r, src5_r, src6_r, src7_r;
    v8i16 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    v8i16 wgt, denom, offset;

    offset_val = (unsigned) offset_in << log2_denom;

    wgt = __msa_fill_h(src_weight);
    offset = __msa_fill_h(offset_val);
    denom = __msa_fill_h(log2_denom);

    for (cnt = 2; cnt--;) {
        LD4(data, stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, src0);
        INSERT_D2_UB(tp2, tp3, src1);
        LD4(data + 4 * stride, stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, src2);
        INSERT_D2_UB(tp2, tp3, src3);
        UNPCK_UB_SH(src0, src0_r, src1_r);
        UNPCK_UB_SH(src1, src2_r, src3_r);
        UNPCK_UB_SH(src2, src4_r, src5_r);
        UNPCK_UB_SH(src3, src6_r, src7_r);
        MUL4(wgt, src0_r, wgt, src1_r, wgt, src2_r, wgt, src3_r, tmp0, tmp1,
             tmp2, tmp3);
        MUL4(wgt, src4_r, wgt, src5_r, wgt, src6_r, wgt, src7_r, tmp4, tmp5,
             tmp6, tmp7);
        ADDS_SH4_SH(tmp0, offset, tmp1, offset, tmp2, offset, tmp3, offset,
                    tmp0, tmp1, tmp2, tmp3);
        ADDS_SH4_SH(tmp4, offset, tmp5, offset, tmp6, offset, tmp7, offset,
                    tmp4, tmp5, tmp6, tmp7);
        MAXI_SH8_SH(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, 0);
        SRLR_H8_SH(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, denom);
        SAT_UH8_SH(tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, 7);
        PCKEV_B4_UB(tmp1, tmp0, tmp3, tmp2, tmp5, tmp4, tmp7, tmp6, src0, src1,
                    src2, src3);
        ST_D8(src0, src1, src2, src3, 0, 1, 0, 1, 0, 1, 0, 1, data, stride);
        data += 8 * stride;
    }
}