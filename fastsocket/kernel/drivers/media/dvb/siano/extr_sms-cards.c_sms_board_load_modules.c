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
#define  SMS1XXX_BOARD_HAUPPAUGE_CATAMOUNT 133 
#define  SMS1XXX_BOARD_HAUPPAUGE_OKEMO_A 132 
#define  SMS1XXX_BOARD_HAUPPAUGE_OKEMO_B 131 
#define  SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD 130 
#define  SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2 129 
#define  SMS1XXX_BOARD_HAUPPAUGE_WINDHAM 128 
 int /*<<< orphan*/  request_module (char*) ; 

int sms_board_load_modules(int id)
{
	switch (id) {
	case SMS1XXX_BOARD_HAUPPAUGE_CATAMOUNT:
	case SMS1XXX_BOARD_HAUPPAUGE_OKEMO_A:
	case SMS1XXX_BOARD_HAUPPAUGE_OKEMO_B:
	case SMS1XXX_BOARD_HAUPPAUGE_WINDHAM:
	case SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD:
	case SMS1XXX_BOARD_HAUPPAUGE_TIGER_MINICARD_R2:
		request_module("smsdvb");
		break;
	default:
		/* do nothing */
		break;
	}
	return 0;
}