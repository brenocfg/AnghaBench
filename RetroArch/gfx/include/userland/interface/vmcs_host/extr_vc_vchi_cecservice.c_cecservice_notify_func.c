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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int32_t ;
typedef  scalar_t__ VCOS_STATUS_T ;
struct TYPE_2__ {int notify_length; scalar_t__ to_exit; int /*<<< orphan*/  notify_data; int /*<<< orphan*/  (* notify_fn ) (int /*<<< orphan*/ ,int,int,int,int,int) ;scalar_t__ physical_address; scalar_t__ logical_address; int /*<<< orphan*/ * notify_buffer; int /*<<< orphan*/ * notify_handle; int /*<<< orphan*/  initialised; } ;
typedef  scalar_t__ CEC_DEVICE_TYPE_T ;
typedef  TYPE_1__ CECSERVICE_HOST_STATE_T ;

/* Variables and functions */
 int CEC_CB_REASON (int) ; 
 int /*<<< orphan*/  VCHI_FLAGS_NONE ; 
 scalar_t__ VCOS_SUCCESS ; 
#define  VC_CEC_BUTTON_PRESSED 137 
#define  VC_CEC_BUTTON_RELEASE 136 
#define  VC_CEC_LOGICAL_ADDR 135 
#define  VC_CEC_LOGICAL_ADDR_LOST 134 
#define  VC_CEC_NOTIFY_NONE 133 
#define  VC_CEC_REMOTE_PRESSED 132 
#define  VC_CEC_REMOTE_RELEASE 131 
#define  VC_CEC_RX 130 
#define  VC_CEC_TOPOLOGY 129 
#define  VC_CEC_TX 128 
 int VC_VTOH32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cecservice_notify_available_event ; 
 int /*<<< orphan*/ * cecservice_notify_strings ; 
 int max_notify_strings ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  vc_cec_log_info (char*,...) ; 
 scalar_t__ vchi_msg_dequeue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 scalar_t__ vcos_event_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *cecservice_notify_func(void *arg) {
   int32_t success;
   CECSERVICE_HOST_STATE_T *state = (CECSERVICE_HOST_STATE_T *) arg;

   vc_cec_log_info("CEC service async thread started");
   while(1) {
      VCOS_STATUS_T status = vcos_event_wait(&cecservice_notify_available_event);
      uint32_t cb_reason_str_idx = max_notify_strings - 1;
      if(status != VCOS_SUCCESS || !state->initialised || state->to_exit)
         break;

      do {
         uint32_t reason, param1, param2, param3, param4;
         //Get all notifications in the queue
         success = vchi_msg_dequeue( state->notify_handle[0], state->notify_buffer, sizeof(state->notify_buffer), &state->notify_length, VCHI_FLAGS_NONE );
         if(success != 0 || state->notify_length < sizeof(uint32_t)*5 ) { //reason + 4x32-bit parameter
            vcos_assert(state->notify_length == sizeof(uint32_t)*5);
            break;
         }

         //if(lock_obtain() != 0)
         //   break;
         //All notifications are of format: reason, param1, param2, param3, param4 (all 32-bit unsigned int)
         reason = VC_VTOH32(state->notify_buffer[0]);
         param1 = VC_VTOH32(state->notify_buffer[1]);
         param2 = VC_VTOH32(state->notify_buffer[2]);
         param3 = VC_VTOH32(state->notify_buffer[3]);
         param4 = VC_VTOH32(state->notify_buffer[4]);
         //lock_release();

         //Store away physical/logical addresses
         if(CEC_CB_REASON(reason) == VC_CEC_LOGICAL_ADDR) {
            state->logical_address = (CEC_DEVICE_TYPE_T) param1;
            state->physical_address = (uint16_t) (param2 & 0xFFFF);
         }

         switch(CEC_CB_REASON(reason)) {
         case VC_CEC_NOTIFY_NONE:
            cb_reason_str_idx = 0; break;
         case VC_CEC_TX:
            cb_reason_str_idx = 1; break;
         case VC_CEC_RX:
            cb_reason_str_idx = 2; break;
         case VC_CEC_BUTTON_PRESSED:
            cb_reason_str_idx = 3; break;
         case VC_CEC_BUTTON_RELEASE:
            cb_reason_str_idx = 4; break;
         case VC_CEC_REMOTE_PRESSED:
            cb_reason_str_idx = 5; break;
         case VC_CEC_REMOTE_RELEASE:
            cb_reason_str_idx = 6; break;
         case VC_CEC_LOGICAL_ADDR:
            cb_reason_str_idx = 7; break;
         case VC_CEC_TOPOLOGY:
            cb_reason_str_idx = 8; break;
         case VC_CEC_LOGICAL_ADDR_LOST:
            cb_reason_str_idx = 9; break;
         }

         vc_cec_log_info("CEC service callback [%s]: 0x%x, 0x%x, 0x%x, 0x%x",
                         cecservice_notify_strings[cb_reason_str_idx], param1, param2, param3, param4);

         if(state->notify_fn) {
            (*state->notify_fn)(state->notify_data, reason, param1, param2, param3, param4);
         } else {
            vc_cec_log_info("CEC service: No callback handler specified, callback [%s] swallowed",
                            cecservice_notify_strings[cb_reason_str_idx]);
         }

      } while(success == 0 && state->notify_length >= sizeof(uint32_t)*5); //read the next message if any
   } //while (1)

   if(state->to_exit)
      vc_cec_log_info("CEC service async thread exiting");

   return 0;
}