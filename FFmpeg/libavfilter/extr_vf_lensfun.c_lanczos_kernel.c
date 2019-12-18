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

/* Variables and functions */
 float M_PI ; 
 float sin (float) ; 

__attribute__((used)) static float lanczos_kernel(float x)
{
    if (x == 0.0f) {
        return 1.0f;
    } else if (x > -2.0f && x < 2.0f) {
        return (2.0f * sin(M_PI * x) * sin(M_PI / 2.0f * x)) / (M_PI * M_PI * x * x);
    } else {
        return 0.0f;
    }
}