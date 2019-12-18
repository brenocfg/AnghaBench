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
typedef  scalar_t__ qboolean ;
struct TYPE_2__ {int numAreas; scalar_t__* areaPortals; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_FloodAreaConnections () ; 
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 TYPE_1__ cm ; 

void	CM_AdjustAreaPortalState( int area1, int area2, qboolean open ) {
	if ( area1 < 0 || area2 < 0 ) {
		return;
	}

	if ( area1 >= cm.numAreas || area2 >= cm.numAreas ) {
		Com_Error (ERR_DROP, "CM_ChangeAreaPortalState: bad area number");
	}

	if ( open ) {
		cm.areaPortals[ area1 * cm.numAreas + area2 ]++;
		cm.areaPortals[ area2 * cm.numAreas + area1 ]++;
	} else {
		cm.areaPortals[ area1 * cm.numAreas + area2 ]--;
		cm.areaPortals[ area2 * cm.numAreas + area1 ]--;
		if ( cm.areaPortals[ area2 * cm.numAreas + area1 ] < 0 ) {
			Com_Error (ERR_DROP, "CM_AdjustAreaPortalState: negative reference count");
		}
	}

	CM_FloodAreaConnections ();
}