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
typedef  scalar_t__ DWORD ;

/* Variables and functions */

__attribute__((used)) static float normalizeAxis(DWORD pos, DWORD min, DWORD max)
{
    float fpos = (float) pos;
    float fmin = (float) min;
    float fmax = (float) max;

    return (2.f * (fpos - fmin) / (fmax - fmin)) - 1.f;
}