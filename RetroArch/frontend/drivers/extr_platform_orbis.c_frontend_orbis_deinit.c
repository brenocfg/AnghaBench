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
 int /*<<< orphan*/  CMD_EVENT_LOG_FILE_DEINIT ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps4LinkFinish () ; 
 int /*<<< orphan*/  verbosity_disable () ; 

__attribute__((used)) static void frontend_orbis_deinit(void *data)
{
   (void)data;
#ifndef IS_SALAMANDER
   verbosity_disable();
#ifdef HAVE_FILE_LOGGER
   command_event(CMD_EVENT_LOG_FILE_DEINIT, NULL);
#endif

#endif
	ps4LinkFinish();
}