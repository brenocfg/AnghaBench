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
typedef  scalar_t__* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 int MAX_MAP_BOUNDS ; 
 int VERTEX_HASH_SHIFT ; 
 int VERTEX_HASH_SIZE ; 

unsigned AAS_HashVec(vec3_t vec)
{
	int x, y;

	x = (MAX_MAP_BOUNDS + (int)(vec[0]+0.5)) >> VERTEX_HASH_SHIFT;
	y = (MAX_MAP_BOUNDS + (int)(vec[1]+0.5)) >> VERTEX_HASH_SHIFT;

	if (x < 0 || x >= VERTEX_HASH_SIZE || y < 0 || y >= VERTEX_HASH_SIZE)
	{
		Log_Print("WARNING! HashVec: point %f %f %f outside valid range\n", vec[0], vec[1], vec[2]);
		Log_Print("This should never happen!\n");
		return -1;
	} //end if
	
	return y*VERTEX_HASH_SIZE + x;
}