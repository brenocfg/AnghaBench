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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * ptr; } ;
struct TYPE_8__ {TYPE_1__ waiter; int /*<<< orphan*/  magic; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ WFC_IPC_MSG_HEADER_T ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_9__ {size_t member_1; TYPE_2__* member_0; } ;
typedef  TYPE_3__ VCHIQ_ELEMENT_T ;
struct TYPE_10__ {int /*<<< orphan*/  service; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VCOS_ALERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_ENXIO ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_MAGIC ; 
 scalar_t__ vchiq_queue_message (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  vcos_verify (int /*<<< orphan*/ ) ; 
 TYPE_5__ wfc_client_ipc ; 
 int /*<<< orphan*/  wfc_client_ipc_release_keep_alive () ; 
 int /*<<< orphan*/  wfc_client_ipc_use_keep_alive () ; 

VCOS_STATUS_T wfc_client_ipc_send(WFC_IPC_MSG_HEADER_T *msg,
                                    size_t size)
{
   VCHIQ_STATUS_T vst;
   VCHIQ_ELEMENT_T elems[] = {{msg, size}};

   vcos_log_trace("%s: type %d, len %d", VCOS_FUNCTION, msg->type, size);

   vcos_assert(size >= sizeof(*msg));

   if (!vcos_verify(wfc_client_ipc.refcount))
   {
      VCOS_ALERT("%s: client uninitialised", VCOS_FUNCTION);
      /* Client has not been initialised */
      return VCOS_EINVAL;
   }

   msg->magic  = WFC_IPC_MSG_MAGIC;
   msg->waiter.ptr = NULL;

   wfc_client_ipc_use_keep_alive();

   vst = vchiq_queue_message(wfc_client_ipc.service, elems, 1);

   wfc_client_ipc_release_keep_alive();

   if (vst != VCHIQ_SUCCESS)
   {
      vcos_log_error("%s: failed to queue, 0x%x", VCOS_FUNCTION, vst);
      return VCOS_ENXIO;
   }

   return VCOS_SUCCESS;
}