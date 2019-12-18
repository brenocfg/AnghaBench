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
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int VCHIQ_REASON_T ;
typedef  int /*<<< orphan*/  VCHIQ_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  UNREACHABLE () ; 
#define  VCHIQ_BULK_RECEIVE_ABORTED 134 
#define  VCHIQ_BULK_RECEIVE_DONE 133 
#define  VCHIQ_BULK_TRANSMIT_ABORTED 132 
#define  VCHIQ_BULK_TRANSMIT_DONE 131 
#define  VCHIQ_MESSAGE_AVAILABLE 130 
#define  VCHIQ_SERVICE_CLOSED 129 
#define  VCHIQ_SERVICE_OPENED 128 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  bulk_event ; 
 int /*<<< orphan*/  khrn_queue ; 
 int /*<<< orphan*/  vchiu_queue_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_event_signal (int /*<<< orphan*/ *) ; 

VCHIQ_STATUS_T khrn_callback(VCHIQ_REASON_T reason, VCHIQ_HEADER_T *header,
                  VCHIQ_SERVICE_HANDLE_T handle, void *bulk_userdata)
{
   switch (reason) {
   case VCHIQ_MESSAGE_AVAILABLE:
      vchiu_queue_push(&khrn_queue, header);
      break;
   case VCHIQ_BULK_TRANSMIT_DONE:
   case VCHIQ_BULK_RECEIVE_DONE:
      vcos_event_signal(&bulk_event);
      break;
   case VCHIQ_SERVICE_OPENED:
   case VCHIQ_SERVICE_CLOSED:
   case VCHIQ_BULK_TRANSMIT_ABORTED:
   case VCHIQ_BULK_RECEIVE_ABORTED:
      UNREACHABLE(); /* not implemented */
   }

   return VCHIQ_SUCCESS;
}