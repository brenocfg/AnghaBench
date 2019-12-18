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
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,float) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int /*<<< orphan*/  Z_ClearZone (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  calloc (int,int) ; 
 int s_smallZoneTotal ; 
 int /*<<< orphan*/  smallzone ; 

void Com_InitSmallZoneMemory( void ) {
	s_smallZoneTotal = 512 * 1024;
	// bk001205 - was malloc
	smallzone = calloc( s_smallZoneTotal, 1 );
	if ( !smallzone ) {
		Com_Error( ERR_FATAL, "Small zone data failed to allocate %1.1f megs", (float)s_smallZoneTotal / (1024*1024) );
	}
	Z_ClearZone( smallzone, s_smallZoneTotal );
	
	return;
}