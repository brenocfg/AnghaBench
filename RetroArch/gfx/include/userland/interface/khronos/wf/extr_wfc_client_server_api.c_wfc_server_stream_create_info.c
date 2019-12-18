#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_7__ {int size; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ WFC_STREAM_INFO_T ;
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
struct TYPE_10__ {void* size; } ;
struct TYPE_8__ {TYPE_4__ header; void* pid_hi; void* pid_lo; TYPE_5__ info; int /*<<< orphan*/  stream; } ;
typedef  TYPE_2__ WFC_IPC_MSG_SS_CREATE_INFO_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_INVALID_HANDLE ; 
 int /*<<< orphan*/  WFC_IPC_MSG_SS_CREATE_INFO ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_1__ const*,void*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,...) ; 
 void* vcos_min (int,int) ; 
 scalar_t__ wfc_client_ipc_sendwait (TYPE_4__*,int,int /*<<< orphan*/ *,size_t*) ; 

WFCNativeStreamType wfc_server_stream_create_info(WFCNativeStreamType stream, const WFC_STREAM_INFO_T *info, uint32_t pid_lo, uint32_t pid_hi)
{
   WFC_IPC_MSG_SS_CREATE_INFO_T msg;
   uint32_t copy_size;
   VCOS_STATUS_T status;
   WFCNativeStreamType result = WFC_INVALID_HANDLE;
   size_t result_len = sizeof(result);

   if (!info)
   {
      vcos_log_error("%s: NULL info pointer passed", VCOS_FUNCTION);
      return WFC_INVALID_HANDLE;
   }

   if (info->size < sizeof(uint32_t))
   {
      vcos_log_error("%s: invalid info pointer passed (size:%u)", VCOS_FUNCTION, info->size);
      return WFC_INVALID_HANDLE;
   }

   vcos_log_trace("%s: stream 0x%x flags 0x%x pid 0x%x%08x", VCOS_FUNCTION, stream, info->flags, pid_hi, pid_lo);

   msg.header.type = WFC_IPC_MSG_SS_CREATE_INFO;
   msg.stream = stream;
   copy_size = vcos_min(info->size, sizeof(msg.info));
   memcpy(&msg.info, info, copy_size);
   msg.info.size = copy_size;
   msg.pid_lo = pid_lo;
   msg.pid_hi = pid_hi;

   status = wfc_client_ipc_sendwait(&msg.header, sizeof(msg), &result, &result_len);

   vcos_log_trace("%s: status 0x%x, result 0x%x", VCOS_FUNCTION, status, result);

   if (status != VCOS_SUCCESS)
      result = WFC_INVALID_HANDLE;

   return result;
}