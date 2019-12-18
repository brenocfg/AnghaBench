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
struct TYPE_2__ {int /*<<< orphan*/  (* GetAccessibleSelectionFromContext ) (long,int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  JOBJECT64 ;
typedef  int /*<<< orphan*/  AccessibleSelection ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  stub1 (long,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ theAccessBridge ; 
 scalar_t__ theAccessBridgeInitializedFlag ; 

JOBJECT64 GetAccessibleSelectionFromContext(long vmID, AccessibleSelection as, int i) {
        if (theAccessBridgeInitializedFlag == TRUE) {
            return theAccessBridge.GetAccessibleSelectionFromContext(vmID, as, i);
        }
        return (JOBJECT64) 0;
    }