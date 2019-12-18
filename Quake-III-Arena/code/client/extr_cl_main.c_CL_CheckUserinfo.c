#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ integer; } ;
struct TYPE_3__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ CA_CHALLENGING ; 
 int /*<<< orphan*/  CL_AddReliableCommand (int /*<<< orphan*/ ) ; 
 int CVAR_USERINFO ; 
 int /*<<< orphan*/  Cvar_InfoString (int) ; 
 TYPE_2__* cl_paused ; 
 TYPE_1__ cls ; 
 int cvar_modifiedFlags ; 
 int /*<<< orphan*/  va (char*,int /*<<< orphan*/ ) ; 

void CL_CheckUserinfo( void ) {
	// don't add reliable commands when not yet connected
	if ( cls.state < CA_CHALLENGING ) {
		return;
	}
	// don't overflow the reliable command buffer when paused
	if ( cl_paused->integer ) {
		return;
	}
	// send a reliable userinfo update if needed
	if ( cvar_modifiedFlags & CVAR_USERINFO ) {
		cvar_modifiedFlags &= ~CVAR_USERINFO;
		CL_AddReliableCommand( va("userinfo \"%s\"", Cvar_InfoString( CVAR_USERINFO ) ) );
	}

}