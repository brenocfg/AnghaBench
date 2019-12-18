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

__attribute__((used)) static int
square_check(double x, double y, double x1, double y1, double x2, double y2)
   /* Is x,y inside the square (x1,y1)..(x2,y2)? */
{
   /* Do a modified Cohen-Sutherland on one point, bit patterns that indicate
    * 'outside' are:
    *
    *   x<x1 | x<y1 | x<x2 | x<y2
    *    0      x      0      x     To the right
    *    1      x      1      x     To the left
    *    x      0      x      0     Below
    *    x      1      x      1     Above
    *
    * So 'inside' is (x<x1) != (x<x2) && (y<y1) != (y<y2);
    */
   return ((x<x1) ^ (x<x2)) & ((y<y1) ^ (y<y2));
}