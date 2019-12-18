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
typedef  int* vec3_t ;

/* Variables and functions */
 int AAS_PointContents (int*) ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 int qfalse ; 
 int qtrue ; 

int AAS_Swimming(vec3_t origin)
{
	vec3_t testorg;

	VectorCopy(origin, testorg);
	testorg[2] -= 2;
	if (AAS_PointContents(testorg) & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER)) return qtrue;
	return qfalse;
}