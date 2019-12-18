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
typedef  int /*<<< orphan*/  client_t ;
struct TYPE_6__ {scalar_t__ integer; } ;
struct TYPE_5__ {int integer; } ;
struct TYPE_4__ {int numSnapshotEntities; scalar_t__ initialized; int /*<<< orphan*/  clients; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  ERR_FATAL ; 
 int PACKET_BACKUP ; 
 int /*<<< orphan*/  SV_BoundMaxClients (int) ; 
 int /*<<< orphan*/  Z_Malloc (int) ; 
 TYPE_3__* com_dedicated ; 
 scalar_t__ qtrue ; 
 TYPE_2__* sv_maxclients ; 
 TYPE_1__ svs ; 

void SV_Startup( void ) {
	if ( svs.initialized ) {
		Com_Error( ERR_FATAL, "SV_Startup: svs.initialized" );
	}
	SV_BoundMaxClients( 1 );

	svs.clients = Z_Malloc (sizeof(client_t) * sv_maxclients->integer );
	if ( com_dedicated->integer ) {
		svs.numSnapshotEntities = sv_maxclients->integer * PACKET_BACKUP * 64;
	} else {
		// we don't need nearly as many when playing locally
		svs.numSnapshotEntities = sv_maxclients->integer * 4 * 64;
	}
	svs.initialized = qtrue;

	Cvar_Set( "sv_running", "1" );
}