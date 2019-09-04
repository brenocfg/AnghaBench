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
typedef  int int64_t ;

/* Variables and functions */
 int FIXP2 ; 
 int INT_PI ; 

__attribute__((used)) static int64_t int_sin(int64_t a)
{
    int64_t a2, res = 0;
    int i;
    if (a < 0) a = INT_PI-a; // 0..inf
    a %= 2 * INT_PI;         // 0..2PI

    if (a >= INT_PI*3/2) a -= 2*INT_PI;  // -PI/2 .. 3PI/2
    if (a >= INT_PI/2  ) a = INT_PI - a; // -PI/2 ..  PI/2

    /* compute sin using Taylor series approximated to the fifth term */
    a2 = (a*a)/(FIXP2);
    for (i = 2; i < 11; i += 2) {
        res += a;
        a = -a*a2 / (FIXP2*i*(i+1));
    }
    return (res + 8)>>4;
}