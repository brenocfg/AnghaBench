#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v4i32 ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CALC_MSE_B (TYPE_2__,TYPE_2__,TYPE_1__) ; 
 int /*<<< orphan*/  HADD_SW_S32 (TYPE_1__) ; 
 int /*<<< orphan*/  INSERT_W4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__) ; 
 int /*<<< orphan*/  LW4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t sse_4width_msa(uint8_t *src_ptr, int32_t src_stride,
                               uint8_t *ref_ptr, int32_t ref_stride,
                               int32_t height)
{
    int32_t ht_cnt;
    uint32_t sse;
    uint32_t src0, src1, src2, src3;
    uint32_t ref0, ref1, ref2, ref3;
    v16u8 src = { 0 };
    v16u8 ref = { 0 };
    v4i32 var = { 0 };

    for (ht_cnt = (height >> 2); ht_cnt--;) {
        LW4(src_ptr, src_stride, src0, src1, src2, src3);
        src_ptr += (4 * src_stride);
        LW4(ref_ptr, ref_stride, ref0, ref1, ref2, ref3);
        ref_ptr += (4 * ref_stride);

        INSERT_W4_UB(src0, src1, src2, src3, src);
        INSERT_W4_UB(ref0, ref1, ref2, ref3, ref);
        CALC_MSE_B(src, ref, var);
    }

    sse = HADD_SW_S32(var);

    return sse;
}