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
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_LOG_CATEGORY ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_CLIENT_SERVER_API_LOGLEVEL ; 
 int /*<<< orphan*/  vcos_log_register (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_unregister (int /*<<< orphan*/ ) ; 
 scalar_t__ wfc_client_ipc_init () ; 

VCOS_STATUS_T wfc_server_connect(void)
{
   VCOS_STATUS_T status;

   vcos_log_set_level(VCOS_LOG_CATEGORY, WFC_CLIENT_SERVER_API_LOGLEVEL);
   vcos_log_register("wfccsapi", VCOS_LOG_CATEGORY);

   status = wfc_client_ipc_init();

   vcos_log_trace("%s: result %d", VCOS_FUNCTION, status);

   if (status != VCOS_SUCCESS)
   {
      vcos_log_unregister(VCOS_LOG_CATEGORY);
   }

   return status;
}