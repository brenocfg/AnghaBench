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
struct em28xx_ir_poll_result {int toggle_bit; int read_count; int rc_address; int* rc_data; } ;
struct em28xx_IR {struct em28xx* dev; } ;
struct em28xx {int (* em28xx_read_reg_req_len ) (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ;} ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  EM2874_R51_IR ; 
 int stub1 (struct em28xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int em2874_polling_getkey(struct em28xx_IR *ir,
				 struct em28xx_ir_poll_result *poll_result)
{
	struct em28xx *dev = ir->dev;
	int rc;
	u8 msg[5] = { 0, 0, 0, 0, 0 };

	/* Read key toggle, brand, and key code
	   on registers 0x51-55
	 */
	rc = dev->em28xx_read_reg_req_len(dev, 0, EM2874_R51_IR,
					  msg, sizeof(msg));
	if (rc < 0)
		return rc;

	/* Infrared toggle (Reg 0x51[7]) */
	poll_result->toggle_bit = (msg[0] >> 7);

	/* Infrared read count (Reg 0x51[6:0] */
	poll_result->read_count = (msg[0] & 0x7f);

	/* Remote Control Address (Reg 0x52) */
	poll_result->rc_address = msg[1];

	/* Remote Control Data (Reg 0x53-55) */
	poll_result->rc_data[0] = msg[2];
	poll_result->rc_data[1] = msg[3];
	poll_result->rc_data[2] = msg[4];

	return 0;
}