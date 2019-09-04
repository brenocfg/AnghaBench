#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float z; } ;

/* Variables and functions */
 int GRIDH ; 
 int GRIDW ; 
 double** p ; 
 TYPE_1__* vertex ; 

void adjust_grid(void)
{
    int pos;
    int x, y;

    for (y = 0; y < GRIDH;  y++)
    {
        for (x = 0;  x < GRIDW;  x++)
        {
            pos = y * GRIDW + x;
            vertex[pos].z = (float) (p[x][y] * (1.0 / 50.0));
        }
    }
}