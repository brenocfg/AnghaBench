#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  string; scalar_t__ integer; } ;
typedef  TYPE_5__ cvar_t ;
struct TYPE_16__ {int color; int numPoints; scalar_t__ points; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_6__ bot_debugpoly_t ;
struct TYPE_18__ {int /*<<< orphan*/  (* Test ) (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* BotLibVarSet ) (char*,int /*<<< orphan*/ ) ;} ;
struct TYPE_17__ {TYPE_4__* clients; } ;
struct TYPE_11__ {int buttons; } ;
struct TYPE_14__ {TYPE_3__* gentity; TYPE_1__ lastUsercmd; } ;
struct TYPE_12__ {int /*<<< orphan*/  currentAngles; int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_13__ {TYPE_2__ r; } ;

/* Variables and functions */
 int BUTTON_ATTACK ; 
 TYPE_5__* Cvar_Get (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ bot_enable ; 
 int bot_maxdebugpolys ; 
 TYPE_9__* botlib_export ; 
 TYPE_6__* debugpolygons ; 
 int /*<<< orphan*/  stub1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ svs ; 

void BotDrawDebugPolygons(void (*drawPoly)(int color, int numPoints, float *points), int value) {
	static cvar_t *bot_debug, *bot_groundonly, *bot_reachability, *bot_highlightarea;
	bot_debugpoly_t *poly;
	int i, parm0;

	if (!debugpolygons)
		return;
	//bot debugging
	if (!bot_debug) bot_debug = Cvar_Get("bot_debug", "0", 0);
	//
	if (bot_enable && bot_debug->integer) {
		//show reachabilities
		if (!bot_reachability) bot_reachability = Cvar_Get("bot_reachability", "0", 0);
		//show ground faces only
		if (!bot_groundonly) bot_groundonly = Cvar_Get("bot_groundonly", "1", 0);
		//get the hightlight area
		if (!bot_highlightarea) bot_highlightarea = Cvar_Get("bot_highlightarea", "0", 0);
		//
		parm0 = 0;
		if (svs.clients[0].lastUsercmd.buttons & BUTTON_ATTACK) parm0 |= 1;
		if (bot_reachability->integer) parm0 |= 2;
		if (bot_groundonly->integer) parm0 |= 4;
		botlib_export->BotLibVarSet("bot_highlightarea", bot_highlightarea->string);
		botlib_export->Test(parm0, NULL, svs.clients[0].gentity->r.currentOrigin, 
			svs.clients[0].gentity->r.currentAngles);
	} //end if
	//draw all debug polys
	for (i = 0; i < bot_maxdebugpolys; i++) {
		poly = &debugpolygons[i];
		if (!poly->inuse) continue;
		drawPoly(poly->color, poly->numPoints, (float *) poly->points);
		//Com_Printf("poly %i, numpoints = %d\n", i, poly->numPoints);
	}
}