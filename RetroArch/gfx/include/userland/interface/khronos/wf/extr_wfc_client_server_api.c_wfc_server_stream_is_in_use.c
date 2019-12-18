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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_SS_IS_IN_USE ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 scalar_t__ wfc_client_server_api_sendwait_stream (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,size_t*) ; 

bool wfc_server_stream_is_in_use(WFCNativeStreamType stream)
{
   VCOS_STATUS_T status;
   uint32_t result = 0;
   size_t result_len = sizeof(result);

   vcos_log_trace("%s: stream 0x%x", VCOS_FUNCTION, stream);

   status = wfc_client_server_api_sendwait_stream(WFC_IPC_MSG_SS_IS_IN_USE, stream, &result, &result_len);

   vcos_log_trace("%s: status 0x%x, result %u", VCOS_FUNCTION, status, result);

   if (status != VCOS_SUCCESS)
      result = 0;

   return result != 0;
}