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
struct TYPE_2__ {int /*<<< orphan*/  (* getAccessibleActions ) (long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  AccessibleContext ;
typedef  int /*<<< orphan*/  AccessibleActions ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  stub1 (long,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ theAccessBridge ; 
 scalar_t__ theAccessBridgeInitializedFlag ; 

BOOL getAccessibleActions(long vmID, AccessibleContext accessibleContext,
                              AccessibleActions *actions) {
        if (theAccessBridgeInitializedFlag == TRUE) {
            return theAccessBridge.getAccessibleActions(vmID, accessibleContext, actions);
        }
        return FALSE;
    }