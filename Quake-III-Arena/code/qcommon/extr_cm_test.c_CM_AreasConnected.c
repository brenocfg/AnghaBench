#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_6__ {int numAreas; TYPE_1__* areas; } ;
struct TYPE_5__ {scalar_t__ integer; } ;
struct TYPE_4__ {scalar_t__ floodnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 TYPE_3__ cm ; 
 TYPE_2__* cm_noAreas ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

qboolean	CM_AreasConnected( int area1, int area2 ) {
#ifndef BSPC
	if ( cm_noAreas->integer ) {
		return qtrue;
	}
#endif

	if ( area1 < 0 || area2 < 0 ) {
		return qfalse;
	}

	if (area1 >= cm.numAreas || area2 >= cm.numAreas) {
		Com_Error (ERR_DROP, "area >= cm.numAreas");
	}

	if (cm.areas[area1].floodnum == cm.areas[area2].floodnum) {
		return qtrue;
	}
	return qfalse;
}