#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * client_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHI_FLAGS_NONE ; 
 scalar_t__ VCOS_FUNCTION ; 
 scalar_t__ VCOS_SUCCESS ; 
 TYPE_1__ tvservice_client ; 
 int /*<<< orphan*/  tvservice_message_available_event ; 
 int /*<<< orphan*/  vchi_msg_dequeue (int /*<<< orphan*/ ,void*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_event_wait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  vcos_log_warn (char*) ; 

__attribute__((used)) static int32_t tvservice_wait_for_reply(void *response, uint32_t max_length) {
   int32_t success = 0;
   uint32_t length_read = 0;
   vcos_log_trace("[%s]", VCOS_FUNCTION);
   do {
      //TODO : we need to deal with messages coming through on more than one connections properly
      //At the moment it will always try to read the first connection if there is something there
      //Check if there is something in the queue, if so return immediately
      //otherwise wait for the semaphore and read again
      success = vchi_msg_dequeue( tvservice_client.client_handle[0], response, max_length, &length_read, VCHI_FLAGS_NONE );
   } while( length_read == 0 && vcos_event_wait(&tvservice_message_available_event) == VCOS_SUCCESS);
   if(length_read) {
      vcos_log_trace("TV service got reply %d bytes", length_read);
   } else {
      vcos_log_warn("TV service wait for reply failed");
   }
   return success;
}