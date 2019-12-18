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
 int* hb_crop_table ; 

__attribute__((used)) static inline int cubic_interpolate_pixel( int y0, int y1, int y2, int y3 )
{
    /* From http://www.neuron2.net/library/cubicinterp.html */
    int result = ( y0 * -3 ) + ( y1 * 23 ) + ( y2 * 23 ) + ( y3 * -3 );
    result = hb_crop_table[(result / 40) + 1024];

    return result;
}