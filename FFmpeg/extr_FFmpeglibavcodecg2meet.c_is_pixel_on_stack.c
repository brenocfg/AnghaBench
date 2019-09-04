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
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int stack_pos; scalar_t__* stack; } ;
typedef  TYPE_1__ ePICContext ;

/* Variables and functions */

__attribute__((used)) static inline int is_pixel_on_stack(const ePICContext *dc, uint32_t pix)
{
    int i;

    for (i = 0; i < dc->stack_pos; i++)
        if (dc->stack[i] == pix)
            break;

    return i != dc->stack_pos;
}