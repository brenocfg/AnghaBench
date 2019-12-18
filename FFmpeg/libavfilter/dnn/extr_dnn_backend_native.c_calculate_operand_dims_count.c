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
typedef  int int32_t ;
struct TYPE_3__ {int* dims; } ;
typedef  TYPE_1__ DnnOperand ;

/* Variables and functions */

int32_t calculate_operand_dims_count(const DnnOperand *oprd)
{
    int32_t result = 1;
    for (int i = 0; i < 4; ++i)
        result *= oprd->dims[i];

    return result;
}