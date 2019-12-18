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
 double ABS (double) ; 
 double MIN (double,double) ; 
 double log (double) ; 
 double pow (double,double) ; 

__attribute__((used)) static void hqdn3d_precalc_coef( short * ct,
                                 double dist25 )
{
    int i;
    double gamma, simil, c;

    gamma = log( 0.25 ) / log( 1.0 - MIN(dist25,252.0)/255.0 - 0.00001 );

    for( i = -255*16; i <= 255*16; i++ )
    {
        /* hqdn3d_lowpass_mul() truncates (not rounds) the diff, use +15/32 as midpoint */
        double f = (i + 15.0/32.0) / 16.0;
        simil = 1.0 - ABS(f) / 255.0;
        c = pow(simil, gamma) * 256.0 * f;
        ct[16*256+i] = (c<0) ? (c-0.5) : (c+0.5);
    }

    ct[0] = (dist25 != 0);
}