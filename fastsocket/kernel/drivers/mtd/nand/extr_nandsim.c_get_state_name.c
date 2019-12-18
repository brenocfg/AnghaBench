#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  NS_ERR (char*) ; 
 int NS_STATE (int /*<<< orphan*/ ) ; 
#define  STATE_ADDR_COLUMN 152 
#define  STATE_ADDR_PAGE 151 
#define  STATE_ADDR_SEC 150 
#define  STATE_ADDR_ZERO 149 
#define  STATE_CMD_ERASE1 148 
#define  STATE_CMD_ERASE2 147 
#define  STATE_CMD_PAGEPROG 146 
#define  STATE_CMD_READ0 145 
#define  STATE_CMD_READ1 144 
#define  STATE_CMD_READID 143 
#define  STATE_CMD_READOOB 142 
#define  STATE_CMD_READSTART 141 
#define  STATE_CMD_RESET 140 
#define  STATE_CMD_RNDOUT 139 
#define  STATE_CMD_RNDOUTSTART 138 
#define  STATE_CMD_SEQIN 137 
#define  STATE_CMD_STATUS 136 
#define  STATE_CMD_STATUS_M 135 
#define  STATE_DATAIN 134 
#define  STATE_DATAOUT 133 
#define  STATE_DATAOUT_ID 132 
#define  STATE_DATAOUT_STATUS 131 
#define  STATE_DATAOUT_STATUS_M 130 
#define  STATE_READY 129 
#define  STATE_UNKNOWN 128 

__attribute__((used)) static char *get_state_name(uint32_t state)
{
	switch (NS_STATE(state)) {
		case STATE_CMD_READ0:
			return "STATE_CMD_READ0";
		case STATE_CMD_READ1:
			return "STATE_CMD_READ1";
		case STATE_CMD_PAGEPROG:
			return "STATE_CMD_PAGEPROG";
		case STATE_CMD_READOOB:
			return "STATE_CMD_READOOB";
		case STATE_CMD_READSTART:
			return "STATE_CMD_READSTART";
		case STATE_CMD_ERASE1:
			return "STATE_CMD_ERASE1";
		case STATE_CMD_STATUS:
			return "STATE_CMD_STATUS";
		case STATE_CMD_STATUS_M:
			return "STATE_CMD_STATUS_M";
		case STATE_CMD_SEQIN:
			return "STATE_CMD_SEQIN";
		case STATE_CMD_READID:
			return "STATE_CMD_READID";
		case STATE_CMD_ERASE2:
			return "STATE_CMD_ERASE2";
		case STATE_CMD_RESET:
			return "STATE_CMD_RESET";
		case STATE_CMD_RNDOUT:
			return "STATE_CMD_RNDOUT";
		case STATE_CMD_RNDOUTSTART:
			return "STATE_CMD_RNDOUTSTART";
		case STATE_ADDR_PAGE:
			return "STATE_ADDR_PAGE";
		case STATE_ADDR_SEC:
			return "STATE_ADDR_SEC";
		case STATE_ADDR_ZERO:
			return "STATE_ADDR_ZERO";
		case STATE_ADDR_COLUMN:
			return "STATE_ADDR_COLUMN";
		case STATE_DATAIN:
			return "STATE_DATAIN";
		case STATE_DATAOUT:
			return "STATE_DATAOUT";
		case STATE_DATAOUT_ID:
			return "STATE_DATAOUT_ID";
		case STATE_DATAOUT_STATUS:
			return "STATE_DATAOUT_STATUS";
		case STATE_DATAOUT_STATUS_M:
			return "STATE_DATAOUT_STATUS_M";
		case STATE_READY:
			return "STATE_READY";
		case STATE_UNKNOWN:
			return "STATE_UNKNOWN";
	}

	NS_ERR("get_state_name: unknown state, BUG\n");
	return NULL;
}