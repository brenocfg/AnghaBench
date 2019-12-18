#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int flip; TYPE_2__ header; void* flags; void* format; void* offset; void* stride; void* height; void* width; void* ustorage; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ WFC_IPC_MSG_SS_SIGNAL_EGLIMAGE_DATA_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_SS_SIGNAL_EGLIMAGE_DATA ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ wfc_client_ipc_send (TYPE_2__*,int) ; 

void wfc_server_stream_signal_eglimage_data(WFCNativeStreamType stream,
      uint32_t ustorage, uint32_t width, uint32_t height, uint32_t stride,
      uint32_t offset, uint32_t format, uint32_t flags, bool flip)
{
   WFC_IPC_MSG_SS_SIGNAL_EGLIMAGE_DATA_T msg;
   VCOS_STATUS_T status;

   memset(&msg, 0, sizeof msg);
   msg.header.type = WFC_IPC_MSG_SS_SIGNAL_EGLIMAGE_DATA;
   msg.stream = stream;
   msg.ustorage = ustorage;
   msg.width = width;
   msg.height = height;
   msg.stride = stride;
   msg.offset = offset;
   msg.format = format;
   msg.flags = flags;
   msg.flip = flip;

   vcos_log_trace("%s: stream 0x%x image storage 0x%x",
         VCOS_FUNCTION, stream, ustorage);

   status = wfc_client_ipc_send(&msg.header, sizeof(msg));

   vcos_assert(status == VCOS_SUCCESS);
}