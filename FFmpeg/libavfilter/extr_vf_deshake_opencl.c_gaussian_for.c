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
 float expf (float) ; 

__attribute__((used)) static float gaussian_for(int x, float sigma) {
    return 1.0f / expf(((float)x * (float)x) / (2.0f * sigma * sigma));
}