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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  SD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_fill_b (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_8bit_value_width8_msa(uint8_t *src, uint8_t val,
                                       int32_t src_stride, int32_t height)
{
    int32_t cnt;
    uint64_t dst0;
    v16u8 val0;

    val0 = (v16u8) __msa_fill_b(val);
    dst0 = __msa_copy_u_d((v2i64) val0, 0);

    for (cnt = (height >> 2); cnt--;) {
        SD4(dst0, dst0, dst0, dst0, src, src_stride);
        src += (4 * src_stride);
    }
}