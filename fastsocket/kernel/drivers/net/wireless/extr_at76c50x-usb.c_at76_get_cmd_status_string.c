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

/* Variables and functions */
 int /*<<< orphan*/  CMD_STATUS_COMPLETE ; 
 int /*<<< orphan*/  CMD_STATUS_FUNCTION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  CMD_STATUS_HOST_FAILURE ; 
 int /*<<< orphan*/  CMD_STATUS_IDLE ; 
 int /*<<< orphan*/  CMD_STATUS_INVALID_PARAMETER ; 
 int /*<<< orphan*/  CMD_STATUS_IN_PROGRESS ; 
 int /*<<< orphan*/  CMD_STATUS_SCAN_FAILED ; 
 int /*<<< orphan*/  CMD_STATUS_TIME_OUT ; 
 int /*<<< orphan*/  CMD_STATUS_UNKNOWN ; 
 int /*<<< orphan*/  MAKE_CMD_STATUS_CASE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *at76_get_cmd_status_string(u8 cmd_status)
{
	switch (cmd_status) {
		MAKE_CMD_STATUS_CASE(CMD_STATUS_IDLE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_COMPLETE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_UNKNOWN);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_INVALID_PARAMETER);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_FUNCTION_NOT_SUPPORTED);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_TIME_OUT);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_IN_PROGRESS);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_HOST_FAILURE);
		MAKE_CMD_STATUS_CASE(CMD_STATUS_SCAN_FAILED);
	}

	return "UNKNOWN";
}