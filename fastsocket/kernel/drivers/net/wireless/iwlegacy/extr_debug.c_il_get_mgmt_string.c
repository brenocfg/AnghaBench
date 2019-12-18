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
 int /*<<< orphan*/  IL_CMD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANAGEMENT_ACTION ; 
 int /*<<< orphan*/  MANAGEMENT_ASSOC_REQ ; 
 int /*<<< orphan*/  MANAGEMENT_ASSOC_RESP ; 
 int /*<<< orphan*/  MANAGEMENT_ATIM ; 
 int /*<<< orphan*/  MANAGEMENT_AUTH ; 
 int /*<<< orphan*/  MANAGEMENT_BEACON ; 
 int /*<<< orphan*/  MANAGEMENT_DEAUTH ; 
 int /*<<< orphan*/  MANAGEMENT_DISASSOC ; 
 int /*<<< orphan*/  MANAGEMENT_PROBE_REQ ; 
 int /*<<< orphan*/  MANAGEMENT_PROBE_RESP ; 
 int /*<<< orphan*/  MANAGEMENT_REASSOC_REQ ; 
 int /*<<< orphan*/  MANAGEMENT_REASSOC_RESP ; 

__attribute__((used)) static const char *
il_get_mgmt_string(int cmd)
{
	switch (cmd) {
	IL_CMD(MANAGEMENT_ASSOC_REQ);
	IL_CMD(MANAGEMENT_ASSOC_RESP);
	IL_CMD(MANAGEMENT_REASSOC_REQ);
	IL_CMD(MANAGEMENT_REASSOC_RESP);
	IL_CMD(MANAGEMENT_PROBE_REQ);
	IL_CMD(MANAGEMENT_PROBE_RESP);
	IL_CMD(MANAGEMENT_BEACON);
	IL_CMD(MANAGEMENT_ATIM);
	IL_CMD(MANAGEMENT_DISASSOC);
	IL_CMD(MANAGEMENT_AUTH);
	IL_CMD(MANAGEMENT_DEAUTH);
	IL_CMD(MANAGEMENT_ACTION);
	default:
		return "UNKNOWN";

	}
}