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
typedef  int /*<<< orphan*/  qnx_input_t ;
typedef  int /*<<< orphan*/  bps_event_t ;

/* Variables and functions */
 int BPS_SUCCESS ; 
 int bps_event_get_domain (int /*<<< orphan*/ *) ; 
 int bps_get_event (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int navigator_get_domain () ; 
 int /*<<< orphan*/  qnx_handle_navigator_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qnx_handle_screen_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int screen_get_domain () ; 

__attribute__((used)) static void qnx_input_poll(void *data)
{
   qnx_input_t *qnx = (qnx_input_t*)data;

   /* Request and process all available BPS events. */
   while(true)
   {
      bps_event_t *event = NULL;
      int rc = bps_get_event(&event, 0);

      if(rc == BPS_SUCCESS)
      {
         int domain;

         if (!event)
            break;

         domain = bps_event_get_domain(event);
         if (domain == navigator_get_domain())
            qnx_handle_navigator_event(qnx, event);
         else if (domain == screen_get_domain())
            qnx_handle_screen_event(qnx, event);
      }
   }
}