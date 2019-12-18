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
 int /*<<< orphan*/  VS_DoForcedTraceLight ; 
 int /*<<< orphan*/  _printf (char*) ; 
 int /*<<< orphan*/  numDrawSurfaces ; 
 int /*<<< orphan*/  qtrue ; 

void VS_DoForcedTraceLightSurfaces(void)
{
	_printf( "forced trace light\n" );
	RunThreadsOnIndividual( numDrawSurfaces, qtrue, VS_DoForcedTraceLight );
}