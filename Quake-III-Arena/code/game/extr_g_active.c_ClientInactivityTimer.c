#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  void* qboolean ;
struct TYPE_9__ {int buttons; scalar_t__ upmove; scalar_t__ rightmove; scalar_t__ forwardmove; } ;
struct TYPE_10__ {int /*<<< orphan*/  localClient; TYPE_1__ cmd; } ;
struct TYPE_11__ {int inactivityTime; void* inactivityWarning; TYPE_2__ pers; } ;
typedef  TYPE_3__ gclient_t ;
struct TYPE_13__ {int integer; } ;
struct TYPE_12__ {int time; int clients; } ;

/* Variables and functions */
 int BUTTON_ATTACK ; 
 TYPE_7__ g_inactivity ; 
 TYPE_6__ level ; 
 void* qfalse ; 
 void* qtrue ; 
 int /*<<< orphan*/  trap_DropClient (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  trap_SendServerCommand (TYPE_3__*,char*) ; 

qboolean ClientInactivityTimer( gclient_t *client ) {
	if ( ! g_inactivity.integer ) {
		// give everyone some time, so if the operator sets g_inactivity during
		// gameplay, everyone isn't kicked
		client->inactivityTime = level.time + 60 * 1000;
		client->inactivityWarning = qfalse;
	} else if ( client->pers.cmd.forwardmove || 
		client->pers.cmd.rightmove || 
		client->pers.cmd.upmove ||
		(client->pers.cmd.buttons & BUTTON_ATTACK) ) {
		client->inactivityTime = level.time + g_inactivity.integer * 1000;
		client->inactivityWarning = qfalse;
	} else if ( !client->pers.localClient ) {
		if ( level.time > client->inactivityTime ) {
			trap_DropClient( client - level.clients, "Dropped due to inactivity" );
			return qfalse;
		}
		if ( level.time > client->inactivityTime - 10000 && !client->inactivityWarning ) {
			client->inactivityWarning = qtrue;
			trap_SendServerCommand( client - level.clients, "cp \"Ten seconds until inactivity drop!\n\"" );
		}
	}
	return qtrue;
}