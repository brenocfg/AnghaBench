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
 long double DP1 ; 
 long double DP2 ; 
 long double DP3 ; 
 long double PIL ; 

__attribute__((used)) static long double redupil(long double x)
{
	long double t;
	long i;

	t = x / PIL;
	if (t >= 0.0L)
		t += 0.5L;
	else
		t -= 0.5L;

	i = t;  /* the multiple */
	t = i;
	t = ((x - t * DP1) - t * DP2) - t * DP3;
	return t;
}