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
 int /*<<< orphan*/  NS_ERR (char*) ; 
 int /*<<< orphan*/  STATE_CMD_ERASE1 ; 
 int /*<<< orphan*/  STATE_CMD_ERASE2 ; 
 int /*<<< orphan*/  STATE_CMD_PAGEPROG ; 
 int /*<<< orphan*/  STATE_CMD_READ0 ; 
 int /*<<< orphan*/  STATE_CMD_READ1 ; 
 int /*<<< orphan*/  STATE_CMD_READID ; 
 int /*<<< orphan*/  STATE_CMD_READOOB ; 
 int /*<<< orphan*/  STATE_CMD_READSTART ; 
 int /*<<< orphan*/  STATE_CMD_RESET ; 
 int /*<<< orphan*/  STATE_CMD_RNDOUT ; 
 int /*<<< orphan*/  STATE_CMD_RNDOUTSTART ; 
 int /*<<< orphan*/  STATE_CMD_SEQIN ; 
 int /*<<< orphan*/  STATE_CMD_STATUS ; 
 int /*<<< orphan*/  STATE_CMD_STATUS_M ; 

__attribute__((used)) static uint32_t get_state_by_command(unsigned command)
{
	switch (command) {
		case NAND_CMD_READ0:
			return STATE_CMD_READ0;
		case NAND_CMD_READ1:
			return STATE_CMD_READ1;
		case NAND_CMD_PAGEPROG:
			return STATE_CMD_PAGEPROG;
		case NAND_CMD_READSTART:
			return STATE_CMD_READSTART;
		case NAND_CMD_READOOB:
			return STATE_CMD_READOOB;
		case NAND_CMD_ERASE1:
			return STATE_CMD_ERASE1;
		case NAND_CMD_STATUS:
			return STATE_CMD_STATUS;
		case NAND_CMD_STATUS_MULTI:
			return STATE_CMD_STATUS_M;
		case NAND_CMD_SEQIN:
			return STATE_CMD_SEQIN;
		case NAND_CMD_READID:
			return STATE_CMD_READID;
		case NAND_CMD_ERASE2:
			return STATE_CMD_ERASE2;
		case NAND_CMD_RESET:
			return STATE_CMD_RESET;
		case NAND_CMD_RNDOUT:
			return STATE_CMD_RNDOUT;
		case NAND_CMD_RNDOUTSTART:
			return STATE_CMD_RNDOUTSTART;
	}

	NS_ERR("get_state_by_command: unknown command, BUG\n");
	return 0;
}