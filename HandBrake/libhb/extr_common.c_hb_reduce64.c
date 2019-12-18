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

void hb_reduce64( int64_t *x, int64_t *y, int64_t num, int64_t den )
{
    // find the greatest common divisor of num & den by Euclid's algorithm
    int64_t n = num, d = den;
    while ( d )
    {
        int64_t t = d;
        d = n % d;
        n = t;
    }

    // at this point n is the gcd. if it's non-zero remove it from num
    // and den. Otherwise just return the original values.
    if ( n )
    {
        num /= n;
        den /= n;
    }

    *x = num;
    *y = den;

}