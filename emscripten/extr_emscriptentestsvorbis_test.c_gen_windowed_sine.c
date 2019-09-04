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
typedef  double len ;

/* Variables and functions */
 double M_PI ; 
 double cos (double) ; 
 int /*<<< orphan*/  memset (float*,int /*<<< orphan*/ ,int) ; 
 float sin (double) ; 

void
gen_windowed_sine (float *data, int len, float maximum)
{    int k ;

    memset (data, 0, len * sizeof (float)) ;

    len /= 2 ;

    for (k = 0 ; k < len ; k++)
    {    data [k] = sin (2.0 * k * M_PI * 1.0 / 32.0 + 0.4) ;

        /* Apply Hanning Window. */
        data [k] *= maximum * (0.5 - 0.5 * cos (2.0 * M_PI * k / ((len) - 1))) ;
        }

    return ;
}