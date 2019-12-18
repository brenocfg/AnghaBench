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
 int /*<<< orphan*/  CONTROL_ACK ; 
 int /*<<< orphan*/  CONTROL_BACK ; 
 int /*<<< orphan*/  CONTROL_BACK_REQ ; 
 int /*<<< orphan*/  CONTROL_CFEND ; 
 int /*<<< orphan*/  CONTROL_CFENDACK ; 
 int /*<<< orphan*/  CONTROL_CTS ; 
 int /*<<< orphan*/  CONTROL_PSPOLL ; 
 int /*<<< orphan*/  CONTROL_RTS ; 
 int /*<<< orphan*/  IL_CMD (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
il_get_ctrl_string(int cmd)
{
	switch (cmd) {
	IL_CMD(CONTROL_BACK_REQ);
	IL_CMD(CONTROL_BACK);
	IL_CMD(CONTROL_PSPOLL);
	IL_CMD(CONTROL_RTS);
	IL_CMD(CONTROL_CTS);
	IL_CMD(CONTROL_ACK);
	IL_CMD(CONTROL_CFEND);
	IL_CMD(CONTROL_CFENDACK);
	default:
		return "UNKNOWN";

	}
}