#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int size; void* flags; } ;
struct TYPE_4__ {TYPE_2__ header; void* pid_hi; void* pid_lo; TYPE_3__ info; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ WFC_IPC_MSG_SS_CREATE_INFO_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_INVALID_HANDLE ; 
 int /*<<< orphan*/  WFC_IPC_MSG_SS_CREATE_INFO ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,scalar_t__,void*,...) ; 
 scalar_t__ wfc_client_ipc_sendwait (TYPE_2__*,int,int /*<<< orphan*/ *,size_t*) ; 

WFCNativeStreamType wfc_server_stream_create(WFCNativeStreamType stream, uint32_t flags, uint32_t pid_lo, uint32_t pid_hi)
{
   WFC_IPC_MSG_SS_CREATE_INFO_T msg;
   VCOS_STATUS_T status;
   WFCNativeStreamType result = WFC_INVALID_HANDLE;
   size_t result_len = sizeof(result);

   vcos_log_trace("%s: stream 0x%x flags 0x%x pid 0x%x%08x", VCOS_FUNCTION, stream, flags, pid_hi, pid_lo);

   msg.header.type = WFC_IPC_MSG_SS_CREATE_INFO;
   msg.stream = stream;
   memset(&msg.info, 0, sizeof(msg.info));
   msg.info.size = sizeof(msg.info);
   msg.info.flags = flags;
   msg.pid_lo = pid_lo;
   msg.pid_hi = pid_hi;

   status = wfc_client_ipc_sendwait(&msg.header, sizeof(msg), &result, &result_len);

   vcos_log_trace("%s: status 0x%x, result 0x%x", VCOS_FUNCTION, status, result);

   if (status != VCOS_SUCCESS)
      result = WFC_INVALID_HANDLE;

   return result;
}