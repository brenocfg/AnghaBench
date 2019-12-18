#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVER_UB2_UB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  INSERT_W2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  INSERT_W4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  LW2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_W2 (TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W4 (TYPE_1__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W8 (TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 TYPE_1__ __msa_aver_u_b (TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void avg_width4_msa(uint8_t *src, uint8_t *dst, int32_t stride,
                           int32_t height)
{
    uint32_t tp0, tp1, tp2, tp3;
    v16u8 src0 = { 0 }, src1 = { 0 }, dst0 = { 0 }, dst1 = { 0 };

    if (8 == height) {
        LW4(src, stride, tp0, tp1, tp2, tp3);
        src += 4 * stride;
        INSERT_W4_UB(tp0, tp1, tp2, tp3, src0);
        LW4(src, stride, tp0, tp1, tp2, tp3);
        INSERT_W4_UB(tp0, tp1, tp2, tp3, src1);
        LW4(dst, stride, tp0, tp1, tp2, tp3);
        INSERT_W4_UB(tp0, tp1, tp2, tp3, dst0);
        LW4(dst + 4 * stride, stride, tp0, tp1, tp2, tp3);
        INSERT_W4_UB(tp0, tp1, tp2, tp3, dst1);
        AVER_UB2_UB(src0, dst0, src1, dst1, dst0, dst1);
        ST_W8(dst0, dst1, 0, 1, 2, 3, 0, 1, 2, 3, dst, stride);
    } else if (4 == height) {
        LW4(src, stride, tp0, tp1, tp2, tp3);
        INSERT_W4_UB(tp0, tp1, tp2, tp3, src0);
        LW4(dst, stride, tp0, tp1, tp2, tp3);
        INSERT_W4_UB(tp0, tp1, tp2, tp3, dst0);
        dst0 = __msa_aver_u_b(src0, dst0);
        ST_W4(dst0, 0, 1, 2, 3, dst, stride);
    } else if (2 == height) {
        LW2(src, stride, tp0, tp1);
        INSERT_W2_UB(tp0, tp1, src0);
        LW2(dst, stride, tp0, tp1);
        INSERT_W2_UB(tp0, tp1, dst0);
        dst0 = __msa_aver_u_b(src0, dst0);
        ST_W2(dst0, 0, 1, dst, stride);
    }
}