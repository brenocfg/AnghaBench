#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  msg ;
struct TYPE_8__ {int /*<<< orphan*/  type; } ;
struct TYPE_6__ {void* ptr; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* ptr ) (void*) ;} ;
struct TYPE_7__ {TYPE_4__ header; TYPE_2__ rects_change_data; TYPE_1__ rects_change_cb; int /*<<< orphan*/  stream; } ;
typedef  TYPE_3__ WFC_IPC_MSG_SS_ON_RECTS_CHANGE_T ;
typedef  int /*<<< orphan*/  (* WFC_CALLBACK_T ) (void*) ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;
typedef  scalar_t__ VCOS_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_SS_ON_RECTS_CHANGE ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (void*),void*) ; 
 int /*<<< orphan*/  vcos_verify (int) ; 
 scalar_t__ wfc_client_ipc_send (TYPE_4__*,int) ; 

void wfc_server_stream_on_rects_change(WFCNativeStreamType stream, WFC_CALLBACK_T rects_change_cb, void *rects_change_data)
{
   WFC_IPC_MSG_SS_ON_RECTS_CHANGE_T msg;
   VCOS_STATUS_T status;

   vcos_log_trace("%s: stream 0x%x cb %p data %p", VCOS_FUNCTION, stream, rects_change_cb, rects_change_data);

   msg.header.type = WFC_IPC_MSG_SS_ON_RECTS_CHANGE;
   msg.stream = stream;
   msg.rects_change_cb.ptr = rects_change_cb;
   msg.rects_change_data.ptr = rects_change_data;

   status = wfc_client_ipc_send(&msg.header, sizeof(msg));

   if (!vcos_verify(status == VCOS_SUCCESS))
   {
      (*rects_change_cb)(rects_change_data);
   }
}