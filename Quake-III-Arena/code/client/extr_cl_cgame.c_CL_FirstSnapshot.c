#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int snapFlags; scalar_t__ serverTime; } ;
struct TYPE_10__ {TYPE_1__ snap; scalar_t__ oldServerTime; scalar_t__ serverTimeDelta; } ;
struct TYPE_9__ {scalar_t__* string; } ;
struct TYPE_8__ {scalar_t__ timeDemoBaseTime; } ;
struct TYPE_7__ {scalar_t__ realtime; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_ACTIVE ; 
 int /*<<< orphan*/  Cbuf_AddText (scalar_t__*) ; 
 int /*<<< orphan*/  Cvar_Set (char*,char*) ; 
 int SNAPFLAG_NOT_ACTIVE ; 
 int /*<<< orphan*/  Sys_BeginProfiling () ; 
 TYPE_5__ cl ; 
 TYPE_4__* cl_activeAction ; 
 TYPE_3__ clc ; 
 TYPE_2__ cls ; 

void CL_FirstSnapshot( void ) {
	// ignore snapshots that don't have entities
	if ( cl.snap.snapFlags & SNAPFLAG_NOT_ACTIVE ) {
		return;
	}
	cls.state = CA_ACTIVE;

	// set the timedelta so we are exactly on this first frame
	cl.serverTimeDelta = cl.snap.serverTime - cls.realtime;
	cl.oldServerTime = cl.snap.serverTime;

	clc.timeDemoBaseTime = cl.snap.serverTime;

	// if this is the first frame of active play,
	// execute the contents of activeAction now
	// this is to allow scripting a timedemo to start right
	// after loading
	if ( cl_activeAction->string[0] ) {
		Cbuf_AddText( cl_activeAction->string );
		Cvar_Set( "activeAction", "" );
	}
	
	Sys_BeginProfiling();
}