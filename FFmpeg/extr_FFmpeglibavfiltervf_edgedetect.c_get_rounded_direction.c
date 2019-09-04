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
 int DIRECTION_45DOWN ; 
 int DIRECTION_45UP ; 
 int DIRECTION_HORIZONTAL ; 
 int DIRECTION_VERTICAL ; 

__attribute__((used)) static int get_rounded_direction(int gx, int gy)
{
    /* reference angles:
     *   tan( pi/8) = sqrt(2)-1
     *   tan(3pi/8) = sqrt(2)+1
     * Gy/Gx is the tangent of the angle (theta), so Gy/Gx is compared against
     * <ref-angle>, or more simply Gy against <ref-angle>*Gx
     *
     * Gx and Gy bounds = [-1020;1020], using 16-bit arithmetic:
     *   round((sqrt(2)-1) * (1<<16)) =  27146
     *   round((sqrt(2)+1) * (1<<16)) = 158218
     */
    if (gx) {
        int tanpi8gx, tan3pi8gx;

        if (gx < 0)
            gx = -gx, gy = -gy;
        gy <<= 16;
        tanpi8gx  =  27146 * gx;
        tan3pi8gx = 158218 * gx;
        if (gy > -tan3pi8gx && gy < -tanpi8gx)  return DIRECTION_45UP;
        if (gy > -tanpi8gx  && gy <  tanpi8gx)  return DIRECTION_HORIZONTAL;
        if (gy >  tanpi8gx  && gy <  tan3pi8gx) return DIRECTION_45DOWN;
    }
    return DIRECTION_VERTICAL;
}