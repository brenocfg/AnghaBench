#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int VCHIQ_REASON_T ;
struct TYPE_4__ {int size; scalar_t__ data; } ;
typedef  TYPE_1__ VCHIQ_HEADER_T ;
typedef  int /*<<< orphan*/  PLATFORM_SEMAPHORE_T ;

/* Variables and functions */
 int ASYNC_COMMAND_DESTROY ; 
#define  ASYNC_COMMAND_POST 136 
#define  ASYNC_COMMAND_WAIT 135 
 int /*<<< orphan*/  KHR_SUCCESS ; 
 int /*<<< orphan*/  UNREACHABLE () ; 
#define  VCHIQ_BULK_RECEIVE_ABORTED 134 
#define  VCHIQ_BULK_RECEIVE_DONE 133 
#define  VCHIQ_BULK_TRANSMIT_ABORTED 132 
#define  VCHIQ_BULK_TRANSMIT_DONE 131 
#define  VCHIQ_MESSAGE_AVAILABLE 130 
#define  VCHIQ_SERVICE_CLOSED 129 
#define  VCHIQ_SERVICE_OPENED 128 
 int /*<<< orphan*/  VCHIQ_SUCCESS ; 
 int /*<<< orphan*/  khronos_platform_semaphore_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khronos_platform_semaphore_create (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  khronos_platform_semaphore_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  khronos_platform_semaphore_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int vchiq_get_client_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_assert_msg (int /*<<< orphan*/ ,char*) ; 

VCHIQ_STATUS_T khan_callback(VCHIQ_REASON_T reason, VCHIQ_HEADER_T *header,
                  VCHIQ_SERVICE_HANDLE_T handle, void *bulk_userdata)
{
   switch (reason) {
   case VCHIQ_MESSAGE_AVAILABLE:
   {
      int32_t *data = (int32_t *) header->data;
      int32_t command = data[0];
      int32_t *msg = &data[1];
      vcos_assert(header->size == 16);

      // TODO should be able to remove this eventually.
      // If incoming message is not addressed to this process, then ignore it.
      // Correct process should then pick it up.
      uint64_t pid = vchiq_get_client_id(handle);
      if((msg[0] != (uint32_t) pid) || (msg[1] != (uint32_t) (pid >> 32)))
      {
         printf("khan_callback: message for wrong process; pid = %X, msg pid = %X\n",
            (uint32_t) pid, msg[0]);
         return VCHIQ_SUCCESS;
      } // if

      if (command == ASYNC_COMMAND_DESTROY)
      {
         /* todo: destroy */
      }
      else
      {
         PLATFORM_SEMAPHORE_T sem;
         if (khronos_platform_semaphore_create(&sem, msg, 1) == KHR_SUCCESS)
         {
            switch (command) {
            case ASYNC_COMMAND_WAIT:
               khronos_platform_semaphore_acquire(&sem);
               break;
            case ASYNC_COMMAND_POST:
               khronos_platform_semaphore_release(&sem);
               break;
            default:
               vcos_assert_msg(0, "khan_callback: unknown message type");
               break;
            }
            khronos_platform_semaphore_destroy(&sem);
         }
      } // else
      vchiq_release_message(handle, header);
      break;
   }
   case VCHIQ_BULK_TRANSMIT_DONE:
   case VCHIQ_BULK_RECEIVE_DONE:
      UNREACHABLE();
      break;
   case VCHIQ_SERVICE_OPENED:
      vcos_assert_msg(0, "khan_callback: VCHIQ_SERVICE_OPENED");
      break;
   case VCHIQ_SERVICE_CLOSED:
      vcos_assert_msg(0, "khan_callback: VCHIQ_SERVICE_CLOSED");
      break;
   case VCHIQ_BULK_TRANSMIT_ABORTED:
   case VCHIQ_BULK_RECEIVE_ABORTED:
   default:
      UNREACHABLE(); /* not implemented */
   }

   return VCHIQ_SUCCESS;
}