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
 int height ; 
 unsigned char* rgb_tab ; 
 int width ; 
 int wrap ; 

__attribute__((used)) static void put_pixel(int x, int y, int r, int g, int b)
{
    unsigned char *p;

    if (x < 0 || x >= width ||
        y < 0 || y >= height)
        return;

    p    = rgb_tab + y * wrap + x * 3;
    p[0] = r;
    p[1] = g;
    p[2] = b;
}