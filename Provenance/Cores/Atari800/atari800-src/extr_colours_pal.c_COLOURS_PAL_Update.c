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
 int /*<<< orphan*/  COLOURS_PAL_GetYUV (double*) ; 
 int /*<<< orphan*/  YUV2RGB (int*,double*) ; 

void COLOURS_PAL_Update(int colourtable[256])
{
	double yuv_table[256*5];
	COLOURS_PAL_GetYUV(yuv_table);
	YUV2RGB(colourtable, yuv_table);
}