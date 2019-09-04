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
struct TYPE_3__ {int* colors; } ;
typedef  TYPE_1__ Palette ;

/* Variables and functions */
 int chroma_diff (int,unsigned int) ; 

__attribute__((used)) static int pixel_color7_slow(Palette * palette, unsigned color)
{
    int i, min = 0x7fffffff;
    int minc = -1;
    for (i = 0; i < 128; i++) {
        int c1 = palette->colors[i];
        int diff = chroma_diff(c1, color);
        if (diff < min) {
            min = diff;
            minc = i;
        }
    }
    return minc;
}