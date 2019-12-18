#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {size_t destlen; int /*<<< orphan*/  sem; void* dest; } ;
typedef  TYPE_2__ WFC_WAITER_T ;
struct TYPE_12__ {TYPE_2__* ptr; } ;
struct TYPE_14__ {TYPE_1__ waiter; int /*<<< orphan*/  magic; } ;
typedef  TYPE_3__ WFC_IPC_MSG_HEADER_T ;
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;
typedef  scalar_t__ VCHIQ_STATUS_T ;
struct TYPE_15__ {size_t member_1; TYPE_3__* member_0; } ;
typedef  TYPE_4__ VCHIQ_ELEMENT_T ;
struct TYPE_16__ {int /*<<< orphan*/  service; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  VCOS_ALERT (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_ENXIO ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  VCOS_SUCCESS ; 
 int /*<<< orphan*/  WFC_IPC_MSG_MAGIC ; 
 scalar_t__ vchiq_queue_message (int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int /*<<< orphan*/  vcos_assert (void*) ; 
 int /*<<< orphan*/  vcos_log_error (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vcos_semaphore_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_verify (int /*<<< orphan*/ ) ; 
 TYPE_6__ wfc_client_ipc ; 
 TYPE_2__* wfc_client_ipc_get_waiter (TYPE_6__*) ; 
 int /*<<< orphan*/  wfc_client_ipc_release_keep_alive () ; 
 int /*<<< orphan*/  wfc_client_ipc_release_waiter (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  wfc_client_ipc_use_keep_alive () ; 

VCOS_STATUS_T wfc_client_ipc_sendwait(WFC_IPC_MSG_HEADER_T *msg,
                                       size_t size,
                                       void *dest,
                                       size_t *destlen)
{
   VCOS_STATUS_T ret = VCOS_SUCCESS;
   WFC_WAITER_T *waiter;
   VCHIQ_STATUS_T vst;
   VCHIQ_ELEMENT_T elems[] = {{msg, size}};

   vcos_assert(size >= sizeof(*msg));
   vcos_assert(dest);

   if (!vcos_verify(wfc_client_ipc.refcount))
   {
      VCOS_ALERT("%s: client uninitialised", VCOS_FUNCTION);
      /* Client has not been initialised */
      return VCOS_EINVAL;
   }

   msg->magic = WFC_IPC_MSG_MAGIC;

   waiter = wfc_client_ipc_get_waiter(&wfc_client_ipc);
   waiter->dest = dest;
   waiter->destlen = *destlen;
   msg->waiter.ptr = waiter;

   wfc_client_ipc_use_keep_alive();

   vcos_log_trace("%s: wait %p, reply to %p", VCOS_FUNCTION, waiter, dest);
   vst = vchiq_queue_message(wfc_client_ipc.service, elems, 1);

   if (vst != VCHIQ_SUCCESS)
   {
      vcos_log_error("%s: failed to queue, 0x%x", VCOS_FUNCTION, vst);
      ret = VCOS_ENXIO;
      goto completed;
   }

   /* now wait for the reply...
    *
    * FIXME: we could do with a timeout here. Need to be careful to cancel
    * the semaphore on a timeout.
    */
   vcos_semaphore_wait(&waiter->sem);
   vcos_log_trace("%s: got reply (len %i/%i)", VCOS_FUNCTION, (int)*destlen, (int)waiter->destlen);
   *destlen = waiter->destlen;

   /* Drop through completion code */

completed:
   wfc_client_ipc_release_waiter(&wfc_client_ipc, waiter);
   wfc_client_ipc_release_keep_alive();

   return ret;
}