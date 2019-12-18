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
 int /*<<< orphan*/  CMD_EVENT_RECORD_DEINIT ; 
 int /*<<< orphan*/  CMD_EVENT_RESUME ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int generic_action_ok_command (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int action_ok_stop_recording(const char *path,
      const char *label, unsigned type, size_t idx, size_t entry_idx)
{
   command_event(CMD_EVENT_RECORD_DEINIT, NULL);
   return generic_action_ok_command(CMD_EVENT_RESUME);
}