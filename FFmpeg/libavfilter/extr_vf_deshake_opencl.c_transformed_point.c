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
struct TYPE_3__ {float* s; } ;
typedef  TYPE_1__ cl_float2 ;

/* Variables and functions */

__attribute__((used)) static cl_float2 transformed_point(float x, float y, float *transform) {
    cl_float2 ret;

    ret.s[0] = x * transform[0] + y * transform[1] + transform[2];
    ret.s[1] = x * transform[3] + y * transform[4] + transform[5];

    return ret;
}