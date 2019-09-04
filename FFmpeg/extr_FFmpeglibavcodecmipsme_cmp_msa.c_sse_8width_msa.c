#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v4i32 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_MSE_B (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  HADD_SW_S32 (TYPE_1__) ; 
 int /*<<< orphan*/  LD_UB4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_D4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t sse_8width_msa(uint8_t *src_ptr, int32_t src_stride,
                               uint8_t *ref_ptr, int32_t ref_stride,
                               int32_t height)
{
    int32_t ht_cnt;
    uint32_t sse;
    v16u8 src0, src1, src2, src3;
    v16u8 ref0, ref1, ref2, ref3;
    v4i32 var = { 0 };

    for (ht_cnt = (height >> 2); ht_cnt--;) {
        LD_UB4(src_ptr, src_stride, src0, src1, src2, src3);
        src_ptr += (4 * src_stride);
        LD_UB4(ref_ptr, ref_stride, ref0, ref1, ref2, ref3);
        ref_ptr += (4 * ref_stride);

        PCKEV_D4_UB(src1, src0, src3, src2, ref1, ref0, ref3, ref2,
                    src0, src1, ref0, ref1);
        CALC_MSE_B(src0, ref0, var);
        CALC_MSE_B(src1, ref1, var);
    }

    sse = HADD_SW_S32(var);

    return sse;
}