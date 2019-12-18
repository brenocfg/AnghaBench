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
typedef  int hil_packet ;

/* Variables and functions */
 int HIL_CMDCT_POL ; 
 int HIL_CMDCT_RPL ; 
 int HIL_CMD_POL ; 
 int HIL_CMD_RPL ; 
 int HIL_ERR_INT ; 
 int HIL_PKT_CMD ; 

__attribute__((used)) static bool hil_dev_is_command_response(hil_packet p)
{
	if ((p & ~HIL_CMDCT_POL) == (HIL_ERR_INT | HIL_PKT_CMD | HIL_CMD_POL))
		return false;

	if ((p & ~HIL_CMDCT_RPL) == (HIL_ERR_INT | HIL_PKT_CMD | HIL_CMD_RPL))
		return false;

	return true;
}