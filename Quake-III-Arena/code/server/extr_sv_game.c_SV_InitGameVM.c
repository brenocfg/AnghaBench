#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_8__ {int /*<<< orphan*/  entityParsePoint; } ;
struct TYPE_7__ {int integer; } ;
struct TYPE_6__ {int /*<<< orphan*/  time; TYPE_1__* clients; } ;
struct TYPE_5__ {int /*<<< orphan*/ * gentity; } ;

/* Variables and functions */
 int /*<<< orphan*/  CM_EntityString () ; 
 int /*<<< orphan*/  Com_Milliseconds () ; 
 int /*<<< orphan*/  GAME_INIT ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gvm ; 
 TYPE_4__ sv ; 
 TYPE_3__* sv_maxclients ; 
 TYPE_2__ svs ; 

__attribute__((used)) static void SV_InitGameVM( qboolean restart ) {
	int		i;

	// start the entity parsing at the beginning
	sv.entityParsePoint = CM_EntityString();

	// clear all gentity pointers that might still be set from
	// a previous level
	// https://zerowing.idsoftware.com/bugzilla/show_bug.cgi?id=522
	//   now done before GAME_INIT call
	for ( i = 0 ; i < sv_maxclients->integer ; i++ ) {
		svs.clients[i].gentity = NULL;
	}
	
	// use the current msec count for a random seed
	// init for this gamestate
	VM_Call( gvm, GAME_INIT, svs.time, Com_Milliseconds(), restart );
}