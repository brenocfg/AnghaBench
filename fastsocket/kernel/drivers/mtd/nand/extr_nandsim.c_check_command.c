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

/* Variables and functions */
#define  NAND_CMD_ERASE1 141 
#define  NAND_CMD_ERASE2 140 
#define  NAND_CMD_PAGEPROG 139 
#define  NAND_CMD_READ0 138 
#define  NAND_CMD_READ1 137 
#define  NAND_CMD_READID 136 
#define  NAND_CMD_READOOB 135 
#define  NAND_CMD_READSTART 134 
#define  NAND_CMD_RESET 133 
#define  NAND_CMD_RNDOUT 132 
#define  NAND_CMD_RNDOUTSTART 131 
#define  NAND_CMD_SEQIN 130 
#define  NAND_CMD_STATUS 129 
#define  NAND_CMD_STATUS_MULTI 128 

__attribute__((used)) static int check_command(int cmd)
{
	switch (cmd) {

	case NAND_CMD_READ0:
	case NAND_CMD_READ1:
	case NAND_CMD_READSTART:
	case NAND_CMD_PAGEPROG:
	case NAND_CMD_READOOB:
	case NAND_CMD_ERASE1:
	case NAND_CMD_STATUS:
	case NAND_CMD_SEQIN:
	case NAND_CMD_READID:
	case NAND_CMD_ERASE2:
	case NAND_CMD_RESET:
	case NAND_CMD_RNDOUT:
	case NAND_CMD_RNDOUTSTART:
		return 0;

	case NAND_CMD_STATUS_MULTI:
	default:
		return 1;
	}
}