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
typedef  int u8 ;

/* Variables and functions */
#define  MCE_CMD_G_REVISION 138 
#define  MCE_CMD_SIG_END 137 
#define  MCE_CMD_S_CARRIER 136 
#define  MCE_CMD_S_RXSENSOR 135 
#define  MCE_CMD_S_TIMEOUT 134 
#define  MCE_CMD_S_TXMASK 133 
#define  MCE_CMD_UNKNOWN 132 
#define  MCE_COMMAND_HEADER 131 
#define  MCE_COMMAND_NULL 130 
#define  MCE_HW_CMD_HEADER 129 
#define  MCE_RSP_PULSE_COUNT 128 

__attribute__((used)) static int mceusb_cmdsize(u8 cmd, u8 subcmd)
{
	int datasize = 0;

	switch (cmd) {
	case MCE_COMMAND_NULL:
		if (subcmd == MCE_HW_CMD_HEADER)
			datasize = 1;
		break;
	case MCE_HW_CMD_HEADER:
		switch (subcmd) {
		case MCE_CMD_G_REVISION:
			datasize = 2;
			break;
		}
	case MCE_COMMAND_HEADER:
		switch (subcmd) {
		case MCE_CMD_UNKNOWN:
		case MCE_CMD_S_CARRIER:
		case MCE_CMD_S_TIMEOUT:
		case MCE_RSP_PULSE_COUNT:
			datasize = 2;
			break;
		case MCE_CMD_SIG_END:
		case MCE_CMD_S_TXMASK:
		case MCE_CMD_S_RXSENSOR:
			datasize = 1;
			break;
		}
	}
	return datasize;
}