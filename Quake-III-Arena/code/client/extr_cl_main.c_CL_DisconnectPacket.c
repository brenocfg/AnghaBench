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
typedef  int /*<<< orphan*/  netadr_t ;
struct TYPE_4__ {int /*<<< orphan*/  remoteAddress; } ;
struct TYPE_6__ {int lastPacketTime; TYPE_1__ netchan; } ;
struct TYPE_5__ {scalar_t__ state; int realtime; } ;

/* Variables and functions */
 scalar_t__ CA_AUTHORIZING ; 
 int /*<<< orphan*/  CL_Disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int /*<<< orphan*/  NET_CompareAdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 
 int /*<<< orphan*/  qtrue ; 

void CL_DisconnectPacket( netadr_t from ) {
	if ( cls.state < CA_AUTHORIZING ) {
		return;
	}

	// if not from our server, ignore it
	if ( !NET_CompareAdr( from, clc.netchan.remoteAddress ) ) {
		return;
	}

	// if we have received packets within three seconds, ignore it
	// (it might be a malicious spoof)
	if ( cls.realtime - clc.lastPacketTime < 3000 ) {
		return;
	}

	// drop the connection
	Com_Printf( "Server disconnected for unknown reason\n" );
	Cvar_Set("com_errorMessage", "Server disconnected for unknown reason\n" );
	CL_Disconnect( qtrue );
}