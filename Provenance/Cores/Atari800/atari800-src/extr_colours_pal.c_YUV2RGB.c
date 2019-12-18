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
 int /*<<< orphan*/  Colours_SetRGB (int,int,int,int,int*) ; 
 int /*<<< orphan*/  Colours_YUV2RGB (double,double,double,double*,double*,double*) ; 

__attribute__((used)) static void YUV2RGB(int colourtable[256], double const yuv_table[256*5])
{
	double const *yuv_ptr = yuv_table;
	int n;
	for (n = 0; n < 256; ++n) {
		double y = *yuv_ptr++;
		double even_u = *yuv_ptr++;
		double odd_u = *yuv_ptr++;
		double even_v = *yuv_ptr++;
		double odd_v = *yuv_ptr++;
		double r, g, b;
		/* The different colors in odd and even lines are not
		   emulated - instead the palette contains averaged values. */
		double u = (even_u + odd_u) / 2.0;
		double v = (even_v + odd_v) / 2.0;
		Colours_YUV2RGB(y, u, v, &r, &g, &b);
		Colours_SetRGB(n, (int) (r * 255), (int) (g * 255), (int) (b * 255), colourtable);
	}
}