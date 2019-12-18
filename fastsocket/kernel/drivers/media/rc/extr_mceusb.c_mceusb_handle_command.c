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
typedef  int u8 ;
struct mceusb_dev {int* buf_in; int tx_mask; int learning_enabled; TYPE_1__* rc; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
#define  MCE_CMD_S_RXSENSOR 130 
#define  MCE_CMD_S_TIMEOUT 129 
#define  MCE_CMD_S_TXMASK 128 
 int /*<<< orphan*/  US_TO_NS (int) ; 

__attribute__((used)) static void mceusb_handle_command(struct mceusb_dev *ir, int index)
{
	u8 hi = ir->buf_in[index + 1] & 0xff;
	u8 lo = ir->buf_in[index + 2] & 0xff;

	switch (ir->buf_in[index]) {
	/* 2-byte return value commands */
	case MCE_CMD_S_TIMEOUT:
		ir->rc->timeout = US_TO_NS((hi << 8 | lo) / 2);
		break;

	/* 1-byte return value commands */
	case MCE_CMD_S_TXMASK:
		ir->tx_mask = hi;
		break;
	case MCE_CMD_S_RXSENSOR:
		ir->learning_enabled = (hi == 0x02);
		break;
	default:
		break;
	}
}