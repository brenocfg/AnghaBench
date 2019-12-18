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
struct st5481_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST5481_CMD_string (unsigned int) ; 
 int /*<<< orphan*/  TXCI ; 
 int /*<<< orphan*/  st5481_usb_device_ctrl_msg (struct st5481_adapter*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void st5481_ph_command(struct st5481_adapter *adapter, unsigned int command)
{
	DBG(8,"command=%s", ST5481_CMD_string(command));

	st5481_usb_device_ctrl_msg(adapter, TXCI, command, NULL, NULL);
}