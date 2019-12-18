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
struct TYPE_3__ {int y; int x; } ;
typedef  TYPE_1__ IntMotionVector ;

/* Variables and functions */
 double M_PI ; 
 double atan2 (int,int) ; 

__attribute__((used)) static double block_angle(int x, int y, int cx, int cy, IntMotionVector *shift)
{
    double a1, a2, diff;

    a1 = atan2(y - cy, x - cx);
    a2 = atan2(y - cy + shift->y, x - cx + shift->x);

    diff = a2 - a1;

    return (diff > M_PI)  ? diff - 2 * M_PI :
           (diff < -M_PI) ? diff + 2 * M_PI :
           diff;
}