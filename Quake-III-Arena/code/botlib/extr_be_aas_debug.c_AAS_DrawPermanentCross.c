#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  float* vec3_t ;
struct TYPE_2__ {int (* DebugLineCreate ) () ;int /*<<< orphan*/  (* DebugLineShow ) (int,float*,float*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_DebugLine (float*,float*,int) ; 
 int /*<<< orphan*/  VectorCopy (float*,float*) ; 
 TYPE_1__ botimport ; 
 int stub1 () ; 
 int /*<<< orphan*/  stub2 (int,float*,float*,int) ; 

void AAS_DrawPermanentCross(vec3_t origin, float size, int color)
{
	int i, debugline;
	vec3_t start, end;

	for (i = 0; i < 3; i++)
	{
		VectorCopy(origin, start);
		start[i] += size;
		VectorCopy(origin, end);
		end[i] -= size;
		AAS_DebugLine(start, end, color);
		debugline = botimport.DebugLineCreate();
		botimport.DebugLineShow(debugline, start, end, color);
	} //end for
}