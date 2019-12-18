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
typedef  int uint32_t ;

/* Variables and functions */

void hex32_to_rgba_normalized(uint32_t hex, float* rgba, float alpha)
{
   rgba[0] = rgba[4] = rgba[8]  = rgba[12] = ((hex >> 16) & 0xFF) * (1.0f / 255.0f); /* r */
   rgba[1] = rgba[5] = rgba[9]  = rgba[13] = ((hex >> 8 ) & 0xFF) * (1.0f / 255.0f); /* g */
   rgba[2] = rgba[6] = rgba[10] = rgba[14] = ((hex >> 0 ) & 0xFF) * (1.0f / 255.0f); /* b */
   rgba[3] = rgba[7] = rgba[11] = rgba[15] = alpha;
}