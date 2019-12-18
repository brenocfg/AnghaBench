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
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {int num_connections; scalar_t__ response_length; scalar_t__ response_buffer; int /*<<< orphan*/ * open_handle; int /*<<< orphan*/  message_available_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHI_FLAGS_NONE ; 
 scalar_t__ VCOS_SUCCESS ; 
 int VC_VTOH32 (int) ; 
 TYPE_1__ gencmd_client ; 
 scalar_t__ lock_obtain () ; 
 int /*<<< orphan*/  lock_release () ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  release_gencmd_service () ; 
 int /*<<< orphan*/  use_gencmd_service () ; 
 scalar_t__ vchi_msg_dequeue (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vcos_event_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ vcos_min (int,int) ; 

int vc_gencmd_read_response (char *response, int maxlen) {
   int i = 0;
   int success = -1;
   int ret_code = 0;
   int32_t sem_ok = 0;

   if(lock_obtain() == 0)
   {
      //Note this will ALWAYS reset response buffer and overwrite any partially read responses
      use_gencmd_service();
      do {
         //TODO : we need to deal with messages coming through on more than one connections properly
         //At the moment it will always try to read the first connection if there is something there
         for(i = 0; i < gencmd_client.num_connections; i++) {
            //Check if there is something in the queue, if so return immediately
            //otherwise wait for the event and read again
            success = (int) vchi_msg_dequeue( gencmd_client.open_handle[i], gencmd_client.response_buffer,
                                              sizeof(gencmd_client.response_buffer), &gencmd_client.response_length, VCHI_FLAGS_NONE);
            if(success == 0) {
               ret_code = VC_VTOH32( *(int *)gencmd_client.response_buffer );
               break;
            } else {
               gencmd_client.response_length = 0;
            }
         }
      } while(!gencmd_client.response_length && vcos_event_wait(&gencmd_client.message_available_event) == VCOS_SUCCESS);

      if(gencmd_client.response_length && sem_ok == 0) {
         gencmd_client.response_length -= sizeof(int); //first word is error code
         memcpy(response, gencmd_client.response_buffer+sizeof(int), (size_t) vcos_min((int)gencmd_client.response_length, (int)maxlen));
      }

      release_gencmd_service();
      lock_release();
   }

   // If we read anything, return the VideoCore code. Error codes < 0 mean we failed to
   // read anything...
   //How do we let the caller know the response code of gencmd?
   //return ret_code;

   return success;
}