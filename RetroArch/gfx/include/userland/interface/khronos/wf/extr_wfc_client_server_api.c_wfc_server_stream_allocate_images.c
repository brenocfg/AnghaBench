#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  result ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int width; int height; int nbufs; TYPE_2__ header; int /*<<< orphan*/  stream; } ;
typedef  TYPE_1__ WFC_IPC_MSG_SS_ALLOCATE_IMAGES_T ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_SS_ALLOCATE_IMAGES ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,scalar_t__,int,...) ; 
 scalar_t__ wfc_client_ipc_sendwait (TYPE_2__*,int,int*,size_t*) ; 

bool wfc_server_stream_allocate_images(WFCNativeStreamType stream, uint32_t width, uint32_t height, uint32_t nbufs)
{
   WFC_IPC_MSG_SS_ALLOCATE_IMAGES_T msg;
   VCOS_STATUS_T status;
   uint32_t result = 0;
   size_t result_len = sizeof(result);

   vcos_log_trace("%s: stream 0x%x width %u height %u nbufs %u", VCOS_FUNCTION, stream, width, height, nbufs);

   msg.header.type = WFC_IPC_MSG_SS_ALLOCATE_IMAGES;
   msg.stream = stream;
   msg.width = width;
   msg.height = height;
   msg.nbufs = nbufs;

   status = wfc_client_ipc_sendwait(&msg.header, sizeof(msg), &result, &result_len);

   vcos_log_trace("%s: status 0x%x result %u", VCOS_FUNCTION, status, result);

   if (status != VCOS_SUCCESS)
      result = 0;

   return result;
}