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
struct TYPE_3__ {int numpoints; int /*<<< orphan*/ * p; } ;
typedef  TYPE_1__ winding_t ;
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  p ;

/* Variables and functions */
 double DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_POINTS_ON_WINDING ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_removed ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int numthreads ; 

void RemoveColinearPoints (winding_t *w)
{
	int		i, j, k;
	vec3_t	v1, v2;
	int		nump;
	vec3_t	p[MAX_POINTS_ON_WINDING];

	nump = 0;
	for (i=0 ; i<w->numpoints ; i++)
	{
		j = (i+1)%w->numpoints;
		k = (i+w->numpoints-1)%w->numpoints;
		VectorSubtract (w->p[j], w->p[i], v1);
		VectorSubtract (w->p[i], w->p[k], v2);
		VectorNormalize(v1);
		VectorNormalize(v2);
		if (DotProduct(v1, v2) < 0.999)
		{
			if (nump >= MAX_POINTS_ON_WINDING)
				Error("RemoveColinearPoints: MAX_POINTS_ON_WINDING");
			VectorCopy (w->p[i], p[nump]);
			nump++;
		}
	}

	if (nump == w->numpoints)
		return;

	if (numthreads == 1)
		c_removed += w->numpoints - nump;
	w->numpoints = nump;
	memcpy (w->p, p, nump*sizeof(p[0]));
}