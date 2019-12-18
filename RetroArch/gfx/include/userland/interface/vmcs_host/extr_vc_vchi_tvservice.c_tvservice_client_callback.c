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
typedef  int /*<<< orphan*/  VCOS_EVENT_T ;
typedef  scalar_t__ VCHI_CALLBACK_REASON_T ;

/* Variables and functions */
 scalar_t__ const VCHI_CALLBACK_MSG_AVAILABLE ; 
 int /*<<< orphan*/  VCOS_FUNCTION ; 
 int /*<<< orphan*/  vcos_event_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_log_trace (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tvservice_client_callback( void *callback_param,
                                       const VCHI_CALLBACK_REASON_T reason,
                                       void *msg_handle ) {
   VCOS_EVENT_T *event = (VCOS_EVENT_T *)callback_param;

   vcos_log_trace("[%s]", VCOS_FUNCTION);
   (void)msg_handle;

   if ( reason != VCHI_CALLBACK_MSG_AVAILABLE || event == NULL)
      return;

   vcos_event_signal(event);
}