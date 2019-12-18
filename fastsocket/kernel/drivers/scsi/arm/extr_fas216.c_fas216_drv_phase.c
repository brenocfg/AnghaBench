#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t phase; } ;
struct TYPE_5__ {TYPE_1__ scsi; } ;
typedef  TYPE_2__ FAS216_Info ;

/* Variables and functions */
 size_t ARRAY_SIZE (char const**) ; 
#define  PHASE_COMMAND 138 
#define  PHASE_DATAIN 137 
#define  PHASE_DATAOUT 136 
#define  PHASE_DONE 135 
#define  PHASE_IDLE 134 
#define  PHASE_MSGIN 133 
#define  PHASE_MSGIN_DISCONNECT 132 
#define  PHASE_MSGOUT 131 
#define  PHASE_MSGOUT_EXPECT 130 
#define  PHASE_SELECTION 129 
#define  PHASE_STATUS 128 

__attribute__((used)) static const char *fas216_drv_phase(FAS216_Info *info)
{
	static const char *phases[] = {
		[PHASE_IDLE]		= "idle",
		[PHASE_SELECTION]	= "selection",
		[PHASE_COMMAND]		= "command",
		[PHASE_DATAOUT]		= "data out",
		[PHASE_DATAIN]		= "data in",
		[PHASE_MSGIN]		= "message in",
		[PHASE_MSGIN_DISCONNECT]= "disconnect",
		[PHASE_MSGOUT_EXPECT]	= "expect message out",
		[PHASE_MSGOUT]		= "message out",
		[PHASE_STATUS]		= "status",
		[PHASE_DONE]		= "done",
	};

	if (info->scsi.phase < ARRAY_SIZE(phases) &&
	    phases[info->scsi.phase])
		return phases[info->scsi.phase];
	return "???";
}