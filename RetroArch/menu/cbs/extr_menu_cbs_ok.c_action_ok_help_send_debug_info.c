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
 int /*<<< orphan*/  CMD_EVENT_SEND_DEBUG_INFO ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int action_ok_help_send_debug_info(const char *path, const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   command_event(CMD_EVENT_SEND_DEBUG_INFO, NULL);
   return 0;
}