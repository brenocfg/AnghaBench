#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
struct TYPE_6__ {int CacheFlag; scalar_t__ LastTick; int LastSwitchType; char* LastStr; } ;
struct TYPE_5__ {int wYear; int wMonth; int wDay; int wHour; int /*<<< orphan*/  wMinute; int /*<<< orphan*/  wSecond; } ;
typedef  TYPE_1__ SYSTEMTIME ;
typedef  TYPE_2__ LOG ;

/* Variables and functions */
#define  LOG_SWITCH_DAY 132 
#define  LOG_SWITCH_HOUR 131 
#define  LOG_SWITCH_MINUTE 130 
#define  LOG_SWITCH_MONTH 129 
#define  LOG_SWITCH_SECOND 128 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  SystemToLocal64 (scalar_t__) ; 
 scalar_t__ TickToTime (scalar_t__) ; 
 int /*<<< orphan*/  UINT64ToSystem (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 

void MakeLogFileNameStringFromTick(LOG *g, char *str, UINT size, UINT64 tick, UINT switch_type)
{
	UINT64 time;
	SYSTEMTIME st;

	// Validate arguments
	if (str == NULL || g == NULL)
	{
		return;
	}

	if (g->CacheFlag)
	{
		if (g->LastTick == tick &&
			g->LastSwitchType == switch_type)
		{
			StrCpy(str, size, g->LastStr);
			return;
		}
	}

	time = TickToTime(tick);
	UINT64ToSystem(&st, SystemToLocal64(time));

	switch (switch_type)
	{
	case LOG_SWITCH_SECOND:	// Secondly basis
		snprintf(str, size, "_%04u%02u%02u_%02u%02u%02u",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
		break;

	case LOG_SWITCH_MINUTE:	// Minutely basis
		snprintf(str, size, "_%04u%02u%02u_%02u%02u",
			st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute);
		break;

	case LOG_SWITCH_HOUR:	// Hourly basis
		snprintf(str, size, "_%04u%02u%02u_%02u", st.wYear, st.wMonth, st.wDay, st.wHour);
		break;

	case LOG_SWITCH_DAY:	// Daily basis
		snprintf(str, size, "_%04u%02u%02u", st.wYear, st.wMonth, st.wDay);
		break;

	case LOG_SWITCH_MONTH:	// Monthly basis
		snprintf(str, size, "_%04u%02u", st.wYear, st.wMonth);
		break;

	default:				// Without switching
		snprintf(str, size, "%s");
		break;
	}

	g->CacheFlag = true;
	g->LastTick = tick;
	g->LastSwitchType = switch_type;
	StrCpy(g->LastStr, sizeof(g->LastStr), str);
}