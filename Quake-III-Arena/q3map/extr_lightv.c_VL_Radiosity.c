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
 int /*<<< orphan*/  RunThreadsOnIndividual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VL_SurfaceRadiosity ; 
 int /*<<< orphan*/  _printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (float*) ; 
 float* lightFloats ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 
 int /*<<< orphan*/  numDrawSurfaces ; 
 int numLightBytes ; 
 float* oldLightFloats ; 
 int /*<<< orphan*/  qtrue ; 

void VL_Radiosity(void) {

	oldLightFloats = lightFloats;
	lightFloats = (float *) malloc(numLightBytes * sizeof(float));
	memcpy(lightFloats, oldLightFloats, numLightBytes * sizeof(float));
	_printf("%7i surfaces\n", numDrawSurfaces);
	RunThreadsOnIndividual( numDrawSurfaces, qtrue, VL_SurfaceRadiosity );
	free(oldLightFloats);
}