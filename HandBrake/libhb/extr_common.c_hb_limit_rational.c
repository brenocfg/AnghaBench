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
 int /*<<< orphan*/  hb_reduce (int*,int*,int,int) ; 

void hb_limit_rational( int *x, int *y, int num, int den, int limit )
{
    hb_reduce( &num, &den, num, den );
    if ( num < limit && den < limit )
    {
        *x = num;
        *y = den;
        return;
    }

    if ( num > den )
    {
        double div = (double)limit / num;
        num = limit;
        den *= div;
    }
    else
    {
        double div = (double)limit / den;
        den = limit;
        num *= div;
    }
    *x = num;
    *y = den;
}