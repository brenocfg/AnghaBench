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
struct moxa_board_conf {int boardType; } ;

/* Variables and functions */
 int EINVAL ; 
#define  MOXA_BOARD_C218_ISA 130 
#define  MOXA_BOARD_C218_PCI 129 
#define  MOXA_BOARD_CP204J 128 

__attribute__((used)) static int moxa_check_fw_model(struct moxa_board_conf *brd, u8 model)
{
	switch (brd->boardType) {
	case MOXA_BOARD_C218_ISA:
	case MOXA_BOARD_C218_PCI:
		if (model != 1)
			goto err;
		break;
	case MOXA_BOARD_CP204J:
		if (model != 3)
			goto err;
		break;
	default:
		if (model != 2)
			goto err;
		break;
	}
	return 0;
err:
	return -EINVAL;
}