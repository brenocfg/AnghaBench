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
typedef  int int32_t ;
typedef  scalar_t__ esp_event_base_t ;

/* Variables and functions */
 scalar_t__ TIMER_EVENTS ; 
#define  TIMER_EVENT_EXPIRY 130 
#define  TIMER_EVENT_STARTED 129 
#define  TIMER_EVENT_STOPPED 128 

__attribute__((used)) static char* get_id_string(esp_event_base_t base, int32_t id) {
    char* event = "";
    if (base == TIMER_EVENTS) {
        switch(id) {
            case TIMER_EVENT_STARTED:
            event = "TIMER_EVENT_STARTED";
            break;
            case TIMER_EVENT_EXPIRY:
            event = "TIMER_EVENT_EXPIRY";
            break;
            case TIMER_EVENT_STOPPED:
            event = "TIMER_EVENT_STOPPED";
            break;
        }
    } else {
        event = "TASK_ITERATION_EVENT";
    }
    return event;
}