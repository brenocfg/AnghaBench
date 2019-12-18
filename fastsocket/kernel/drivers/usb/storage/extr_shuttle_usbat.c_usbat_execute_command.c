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
struct us_data {int /*<<< orphan*/  send_ctrl_pipe; } ;

/* Variables and functions */
 int /*<<< orphan*/  USBAT_CMD_EXEC_CMD ; 
 int usb_stor_ctrl_transfer (struct us_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,unsigned int) ; 

__attribute__((used)) static int usbat_execute_command(struct us_data *us,
								 unsigned char *commands,
								 unsigned int len)
{
	return usb_stor_ctrl_transfer(us, us->send_ctrl_pipe,
								  USBAT_CMD_EXEC_CMD, 0x40, 0, 0,
								  commands, len);
}