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
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ wfc_client_ipc_deinit () ; 

void wfc_server_disconnect(void)
{
   vcos_log_trace("%s: called", VCOS_FUNCTION);

   if (wfc_client_ipc_deinit())
   {
      vcos_log_unregister(VCOS_LOG_CATEGORY);
   }
}