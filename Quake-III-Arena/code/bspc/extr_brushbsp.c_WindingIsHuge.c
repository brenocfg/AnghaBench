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
struct TYPE_3__ {int numpoints; int** p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int qboolean ;

/* Variables and functions */
 int BOGUS_RANGE ; 

qboolean WindingIsHuge (winding_t *w)
{
	int		i, j;

	for (i=0 ; i<w->numpoints ; i++)
	{
		for (j=0 ; j<3 ; j++)
			if (w->p[i][j] < -BOGUS_RANGE+1 || w->p[i][j] > BOGUS_RANGE-1)
				return true;
	}
	return false;
}