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
typedef  int grank_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  menu; } ;

/* Variables and functions */
#define  QGR_STATUS_ACTIVE 137 
#define  QGR_STATUS_BAD_PASSWORD 136 
#define  QGR_STATUS_ERROR 135 
#define  QGR_STATUS_INVALIDUSER 134 
#define  QGR_STATUS_NEW 133 
#define  QGR_STATUS_NO_MEMBERSHIP 132 
#define  QGR_STATUS_NO_USER 131 
#define  QGR_STATUS_PENDING 130 
#define  QGR_STATUS_SPECTATOR 129 
#define  QGR_STATUS_TIMEOUT 128 
 int /*<<< orphan*/  RankStatus_MenuInit () ; 
 int /*<<< orphan*/  UI_ForceMenuOff () ; 
 int /*<<< orphan*/  UI_PushMenu (int /*<<< orphan*/ *) ; 
 TYPE_1__ s_rankstatus ; 
 char* s_rankstatus_message ; 
 int s_status ; 
 int /*<<< orphan*/  trap_CL_UI_RankUserReset () ; 
 scalar_t__ trap_Cvar_VariableValue (char*) ; 

void UI_RankStatusMenu( void ) {

	s_status = (grank_status_t)trap_Cvar_VariableValue("client_status");

	switch( s_status )
	{
	case QGR_STATUS_NEW:
		return;
	case QGR_STATUS_PENDING:
		// GRANK_FIXME
		return;
	case QGR_STATUS_NO_USER:
		// GRANK_FIXME - get this when user exists
		s_rankstatus_message = "Username unavailable";
		break;
	case QGR_STATUS_BAD_PASSWORD:
		s_rankstatus_message = "Invalid password";
		break;
	case QGR_STATUS_TIMEOUT:
		s_rankstatus_message = "Timed out";
		break;
	case QGR_STATUS_NO_MEMBERSHIP:
		s_rankstatus_message = "No membership";
		break;
	case QGR_STATUS_INVALIDUSER:
		s_rankstatus_message = "Validation failed";
		break;
	case QGR_STATUS_ERROR:
		s_rankstatus_message = "Error";
		break;
	case QGR_STATUS_SPECTATOR:
	case QGR_STATUS_ACTIVE:
		UI_ForceMenuOff();
		return;
	default:
		return;
	}
	RankStatus_MenuInit();
	trap_CL_UI_RankUserReset();
	UI_PushMenu ( &s_rankstatus.menu );
}