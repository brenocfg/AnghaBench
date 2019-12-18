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
struct TYPE_2__ {int (* getEventsWaiting ) () ;} ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ TRUE ; 
 int stub1 () ; 
 TYPE_1__ theAccessBridge ; 
 scalar_t__ theAccessBridgeInitializedFlag ; 

int getEventsWaiting() {
        if (theAccessBridgeInitializedFlag == TRUE) {
            return theAccessBridge.getEventsWaiting();
        }
        return FALSE;
    }