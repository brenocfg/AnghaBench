#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ST_UB (TYPE_1__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void memset_zero_16width_msa(uint8_t *src, int32_t stride,
                                    int32_t height)
{
    int8_t cnt;
    v16u8 zero = { 0 };

    for (cnt = (height / 2); cnt--;) {
        ST_UB(zero, src);
        src += stride;
        ST_UB(zero, src);
        src += stride;
    }
}