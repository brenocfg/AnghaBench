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
 long double pS0 ; 
 long double pS1 ; 
 long double pS2 ; 
 long double pS3 ; 
 long double pS4 ; 
 long double pS5 ; 
 long double pS6 ; 
 long double qS1 ; 
 long double qS2 ; 
 long double qS3 ; 
 long double qS4 ; 
 long double qS5 ; 

long double __invtrigl_R(long double z)
{
	long double p, q;
	p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*(pS5+z*pS6))))));
	q = 1.0+z*(qS1+z*(qS2+z*(qS3+z*(qS4+z*qS5))));
	return p/q;
}