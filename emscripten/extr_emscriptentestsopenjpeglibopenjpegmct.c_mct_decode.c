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

void mct_decode(
		int* restrict c0,
		int* restrict c1, 
		int* restrict c2, 
		int n)
{
	int i;
	for (i = 0; i < n; ++i) {
		int y = c0[i];
		int u = c1[i];
		int v = c2[i];
		int g = y - ((u + v) >> 2);
		int r = v + g;
		int b = u + g;
		c0[i] = r;
		c1[i] = g;
		c2[i] = b;
	}
}