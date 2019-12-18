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
typedef  int /*<<< orphan*/  jint ;
struct TYPE_2__ {int /*<<< orphan*/  (* getAccessibleHyperlink ) (long const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  AccessibleHypertext ;
typedef  int /*<<< orphan*/  AccessibleHyperlinkInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  stub1 (long const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 TYPE_1__ theAccessBridge ; 
 scalar_t__ theAccessBridgeInitializedFlag ; 

BOOL getAccessibleHyperlink(const long vmID,
                                const AccessibleHypertext hypertext,
                                const jint nIndex,
                                /* OUT */ AccessibleHyperlinkInfo *hyperlinkInfo) {

        if (theAccessBridgeInitializedFlag == TRUE) {
            return theAccessBridge.getAccessibleHyperlink(vmID,
                                                          hypertext,
                                                          nIndex,
                                                          hyperlinkInfo);
        }
        return FALSE;
    }