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
struct gpu_callback_s {int /*<<< orphan*/  cookie; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  VCHIQ_STATUS_T ;
typedef  int /*<<< orphan*/  VCHIQ_SERVICE_HANDLE_T ;
typedef  int VCHIQ_REASON_T ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ VCHIQ_HEADER_T ;

/* Variables and functions */
#define  VCHIQ_MESSAGE_AVAILABLE 128 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchiq_release_message (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static VCHIQ_STATUS_T gpuserv_callback( VCHIQ_REASON_T reason,
                                        VCHIQ_HEADER_T *header,
                                        VCHIQ_SERVICE_HANDLE_T service,
                                        void *bulk_userdata )
{
   // reason is one of VCHIQ_MESSAGE_AVAILABLE, VCHIQ_BULK_TRANSMIT_DONE, VCHIQ_BULK_RECEIVE_DONE
   switch (reason)
   {
      case VCHIQ_MESSAGE_AVAILABLE:
      {
         struct gpu_callback_s *c = (struct gpu_callback_s *)header->data;
         if (c->func)
            c->func(c->cookie);
         vchiq_release_message(service, header);
         break;
      }
      default:
        ;
   }
   return 0; // Releases any command message (VCHIQ_MESSAGE_AVAILABLE), ignored otherwise
}