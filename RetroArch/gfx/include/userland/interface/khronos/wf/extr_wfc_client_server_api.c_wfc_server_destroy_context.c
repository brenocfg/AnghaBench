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
typedef  int /*<<< orphan*/  WFCContext ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_DESTROY_CONTEXT ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wfc_client_server_api_send_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wfc_server_destroy_context(WFCContext context)
{
   VCOS_STATUS_T status;

   vcos_log_trace("%s: context 0x%x", VCOS_FUNCTION, context);

   status = wfc_client_server_api_send_context(WFC_IPC_MSG_DESTROY_CONTEXT, context);

   vcos_assert(status == VCOS_SUCCESS);
}