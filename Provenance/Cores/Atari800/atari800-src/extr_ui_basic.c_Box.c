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
 int /*<<< orphan*/  Plot (int,int,int,int,int) ; 

__attribute__((used)) static void Box(int fg, int bg, int x1, int y1, int x2, int y2)
{
	int x;
	int y;

	for (x = x1 + 1; x < x2; x++) {
		Plot(fg, bg, 18, x, y1);
		Plot(fg, bg, 18, x, y2);
	}

	for (y = y1 + 1; y < y2; y++) {
		Plot(fg, bg, 124, x1, y);
		Plot(fg, bg, 124, x2, y);
	}

	Plot(fg, bg, 17, x1, y1);
	Plot(fg, bg, 5, x2, y1);
	Plot(fg, bg, 3, x2, y2);
	Plot(fg, bg, 26, x1, y2);
}