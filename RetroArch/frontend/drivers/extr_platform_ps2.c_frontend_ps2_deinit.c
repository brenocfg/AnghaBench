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
 int /*<<< orphan*/  CDVD_Stop () ; 
 int /*<<< orphan*/  CMD_EVENT_LOG_FILE_DEINIT ; 
 int /*<<< orphan*/  Exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _free_ps2_io () ; 
 int /*<<< orphan*/  audsrv_quit () ; 
 int /*<<< orphan*/  command_event (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileXioExit () ; 
 int /*<<< orphan*/  padEnd () ; 
 int /*<<< orphan*/  verbosity_disable () ; 

__attribute__((used)) static void frontend_ps2_deinit(void *data)
{
   (void)data;
#if defined(HAVE_FILE_LOGGER)
   verbosity_disable();
   command_event(CMD_EVENT_LOG_FILE_DEINIT, NULL);
#endif
   _free_ps2_io();
   CDVD_Stop();
   padEnd();
   audsrv_quit();
   fileXioExit();
   Exit(0);
}