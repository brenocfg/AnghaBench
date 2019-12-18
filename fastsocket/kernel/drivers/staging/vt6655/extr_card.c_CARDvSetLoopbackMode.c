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
typedef  int WORD ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  CARD_LB_MAC 130 
#define  CARD_LB_NONE 129 
#define  CARD_LB_PHY 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOBYTE (int) ; 
 int /*<<< orphan*/  MACvSetLoopbackMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CARDvSetLoopbackMode (DWORD_PTR dwIoBase, WORD wLoopbackMode)
{
    switch(wLoopbackMode) {
    case CARD_LB_NONE:
    case CARD_LB_MAC:
    case CARD_LB_PHY:
        break;
    default:
        ASSERT(FALSE);
        break;
    }
    // set MAC loopback
    MACvSetLoopbackMode(dwIoBase, LOBYTE(wLoopbackMode));
    // set Baseband loopback
}