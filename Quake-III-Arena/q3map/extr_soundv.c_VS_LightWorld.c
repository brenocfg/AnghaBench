#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ numvolumes; } ;
struct TYPE_3__ {scalar_t__ insolid; } ;

/* Variables and functions */
 float FloatForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetVectorForKey (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VS_DoForcedTraceLightSurfaces () ; 
 int /*<<< orphan*/  VS_FloodLightThread ; 
 int /*<<< orphan*/  VS_Radiosity () ; 
 int /*<<< orphan*/  VS_StoreLightmap () ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _printf (char*,int) ; 
 int /*<<< orphan*/ * entities ; 
 int /*<<< orphan*/  lightAmbientColor ; 
 TYPE_2__** lsurfaceTest ; 
 int numDrawSurfaces ; 
 int numvsounds ; 
 int /*<<< orphan*/  qtrue ; 
 int radiosity ; 
 int radiosity_scale ; 
 TYPE_1__** vsounds ; 

void VS_LightWorld(void)
{
	int i, numcastedvolumes, numvsoundsinsolid;
	float f;

	// find the optional world ambient
	GetVectorForKey( &entities[0], "_color", lightAmbientColor );
	f = FloatForKey( &entities[0], "ambient" );
	VectorScale( lightAmbientColor, f, lightAmbientColor );
	/*
	_printf("\r%6d lights out of %d", 0, numvsounds);
	for (i = 0; i < numvsounds; i++)
	{
		_printf("\r%6d", i);
		VS_FloodLight(vsounds[i]);
	}
	_printf("\r%6d lights out of %d\n", i, numvsounds);
	*/
	_printf("%7i lights\n", numvsounds);
	RunThreadsOnIndividual( numvsounds, qtrue, VS_FloodLightThread );

	numcastedvolumes = 0;
	for ( i = 0 ; i < numDrawSurfaces ; i++ ) {
		if (lsurfaceTest[i])
			numcastedvolumes += lsurfaceTest[i]->numvolumes;
	}
	_printf("%7i light volumes casted\n", numcastedvolumes);
	numvsoundsinsolid = 0;
	for (i = 0; i < numvsounds; i++)
	{
		if (vsounds[i]->insolid)
			numvsoundsinsolid++;
	}
	_printf("%7i lights in solid\n", numvsoundsinsolid);
	//
	radiosity_scale = 1;
	for (i = 0; i < radiosity; i++) {
		VS_Radiosity();
		radiosity_scale <<= 1;
	}
	//
	VS_StoreLightmap();
	// redo surfaces with the old light algorithm when needed
	VS_DoForcedTraceLightSurfaces();
}