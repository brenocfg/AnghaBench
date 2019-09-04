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
struct TYPE_3__ {int* gradient_scale; } ;
typedef  TYPE_1__ MotionPixelsContext ;

/* Variables and functions */

__attribute__((used)) static int mp_gradient(MotionPixelsContext *mp, int component, int v)
{
    int delta;

    delta = (v - 7) * mp->gradient_scale[component];
    mp->gradient_scale[component] = (v == 0 || v == 14) ? 2 : 1;
    return delta;
}