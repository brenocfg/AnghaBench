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
 float DP1 ; 
 float DP2 ; 
 float DP3 ; 
 scalar_t__ M_PI ; 

__attribute__((used)) static float _redupif(float xx)
{
	float x, t;
	long i;

	x = xx;
	t = x/(float)M_PI;
	if (t >= 0.0f)
		t += 0.5f;
	else
		t -= 0.5f;

	i = t;  /* the multiple */
	t = i;
	t = ((x - t * DP1) - t * DP2) - t * DP3;
	return t;
}