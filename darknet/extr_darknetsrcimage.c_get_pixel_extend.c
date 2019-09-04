#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int w; int h; int c; } ;
typedef  TYPE_1__ image ;

/* Variables and functions */
 float get_pixel (TYPE_1__,int,int,int) ; 

__attribute__((used)) static float get_pixel_extend(image m, int x, int y, int c)
{
    if(x < 0 || x >= m.w || y < 0 || y >= m.h) return 0;
    /*
    if(x < 0) x = 0;
    if(x >= m.w) x = m.w-1;
    if(y < 0) y = 0;
    if(y >= m.h) y = m.h-1;
    */
    if(c < 0 || c >= m.c) return 0;
    return get_pixel(m, x, y, c);
}