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
struct TYPE_2__ {int /*<<< orphan*/  (* getTextAttributesInRange ) (long const,int /*<<< orphan*/  const,int const,int const,int /*<<< orphan*/ *,short*) ;} ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  AccessibleTextAttributesInfo ;
typedef  int /*<<< orphan*/  AccessibleContext ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  stub1 (long const,int /*<<< orphan*/  const,int const,int const,int /*<<< orphan*/ *,short*) ; 
 TYPE_1__ theAccessBridge ; 
 scalar_t__ theAccessBridgeInitializedFlag ; 

BOOL getTextAttributesInRange(const long vmID, const AccessibleContext accessibleContext,
                                  const int startIndex, const int endIndex,
                                  AccessibleTextAttributesInfo *attributes, short *len) {
        if (theAccessBridgeInitializedFlag == TRUE) {
            return theAccessBridge.getTextAttributesInRange(vmID, accessibleContext, startIndex,
                                                            endIndex, attributes, len);
        }
        return FALSE;
    }