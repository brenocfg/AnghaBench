#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_14__ {scalar_t__ modified; } ;
struct TYPE_13__ {scalar_t__ modified; } ;
struct TYPE_12__ {scalar_t__ modified; } ;
struct TYPE_11__ {scalar_t__ modified; } ;
struct TYPE_10__ {scalar_t__ modified; } ;
struct TYPE_9__ {scalar_t__ modified; } ;
struct TYPE_8__ {scalar_t__ modified; } ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 void* Cvar_Get (char*,char*,int) ; 
 TYPE_7__* net_noipx ; 
 TYPE_6__* net_noudp ; 
 TYPE_5__* net_socksEnabled ; 
 TYPE_4__* net_socksPassword ; 
 TYPE_3__* net_socksPort ; 
 TYPE_2__* net_socksServer ; 
 TYPE_1__* net_socksUsername ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

__attribute__((used)) static qboolean NET_GetCvars( void ) {
	qboolean	modified;

	modified = qfalse;

	if( net_noudp && net_noudp->modified ) {
		modified = qtrue;
	}
	net_noudp = Cvar_Get( "net_noudp", "0", CVAR_LATCH | CVAR_ARCHIVE );

	if( net_noipx && net_noipx->modified ) {
		modified = qtrue;
	}
	net_noipx = Cvar_Get( "net_noipx", "0", CVAR_LATCH | CVAR_ARCHIVE );


	if( net_socksEnabled && net_socksEnabled->modified ) {
		modified = qtrue;
	}
	net_socksEnabled = Cvar_Get( "net_socksEnabled", "0", CVAR_LATCH | CVAR_ARCHIVE );

	if( net_socksServer && net_socksServer->modified ) {
		modified = qtrue;
	}
	net_socksServer = Cvar_Get( "net_socksServer", "", CVAR_LATCH | CVAR_ARCHIVE );

	if( net_socksPort && net_socksPort->modified ) {
		modified = qtrue;
	}
	net_socksPort = Cvar_Get( "net_socksPort", "1080", CVAR_LATCH | CVAR_ARCHIVE );

	if( net_socksUsername && net_socksUsername->modified ) {
		modified = qtrue;
	}
	net_socksUsername = Cvar_Get( "net_socksUsername", "", CVAR_LATCH | CVAR_ARCHIVE );

	if( net_socksPassword && net_socksPassword->modified ) {
		modified = qtrue;
	}
	net_socksPassword = Cvar_Get( "net_socksPassword", "", CVAR_LATCH | CVAR_ARCHIVE );


	return modified;
}