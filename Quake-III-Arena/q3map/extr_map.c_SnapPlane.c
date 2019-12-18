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
typedef  scalar_t__ vec_t ;
typedef  int /*<<< orphan*/  vec3_t ;

/* Variables and functions */
 scalar_t__ DIST_EPSILON ; 
 scalar_t__ Q_rint (scalar_t__) ; 
 int /*<<< orphan*/  SnapVector (int /*<<< orphan*/ ) ; 
 scalar_t__ fabs (scalar_t__) ; 

void	SnapPlane (vec3_t normal, vec_t *dist)
{
	SnapVector (normal);

	if (fabs(*dist-Q_rint(*dist)) < DIST_EPSILON)
		*dist = Q_rint(*dist);
}