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
typedef  int uint8_t ;

/* Variables and functions */
#define  EventIDNotificationAdded 130 
#define  EventIDNotificationModified 129 
#define  EventIDNotificationRemoved 128 

char *EventID_to_String(uint8_t EventID)
{
    char *str = NULL;
    switch (EventID)
    {
        case EventIDNotificationAdded:
            str = "New message";
            break;
        case EventIDNotificationModified:
            str = "Modified message";
            break;
        case EventIDNotificationRemoved:
            str = "Removed message";
            break;
        default:
            str = "unknown EventID";
            break;
    }
    return str;
}