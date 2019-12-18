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
struct TYPE_2__ {int (* getAccessibleHypertextLinkIndex ) (long const,int /*<<< orphan*/  const,int const) ;} ;
typedef  int /*<<< orphan*/  AccessibleHypertext ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 int stub1 (long const,int /*<<< orphan*/  const,int const) ; 
 TYPE_1__ theAccessBridge ; 
 scalar_t__ theAccessBridgeInitializedFlag ; 

jint getAccessibleHypertextLinkIndex(const long vmID,
                                         const AccessibleHypertext hypertext,
                                         const jint nIndex) {

        if (theAccessBridgeInitializedFlag == TRUE) {
            return theAccessBridge.getAccessibleHypertextLinkIndex(vmID,
                                                                   hypertext,
                                                                   nIndex);
        }
        return -1;
    }