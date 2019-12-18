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
typedef  int jint ;
struct TYPE_2__ {int (* getAccessibleTableColumn ) (long,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  AccessibleTable ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int stub1 (long,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ theAccessBridge ; 
 scalar_t__ theAccessBridgeInitializedFlag ; 

jint
    getAccessibleTableColumn(long vmID, AccessibleTable table, jint index) {
        if (theAccessBridgeInitializedFlag == TRUE) {
            return theAccessBridge.getAccessibleTableColumn(vmID, table, index);
        }
        return -1;
    }