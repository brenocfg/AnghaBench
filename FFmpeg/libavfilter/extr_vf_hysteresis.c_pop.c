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
typedef  int uint32_t ;
struct TYPE_3__ {int* xy; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ HysteresisContext ;

/* Variables and functions */

__attribute__((used)) static void pop(HysteresisContext *s, int *x, int *y)
{
    uint32_t val = s->xy[s->index--];

    *x = val >> 16;
    *y = val & 0x0000FFFF;
}