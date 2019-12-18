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
struct dc390_srb {int MsgCnt; TYPE_1__* pSRBDCB; int /*<<< orphan*/ * MsgOutBuf; } ;
struct dc390_acb {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  DCBFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT ; 
 int /*<<< orphan*/  ABORT_DEV_ ; 
 int /*<<< orphan*/  DC390_ENABLE_MSGOUT ; 

__attribute__((used)) static void
dc390_EnableMsgOut_Abort ( struct dc390_acb* pACB, struct dc390_srb* pSRB )
{
    pSRB->MsgOutBuf[0] = ABORT; 
    pSRB->MsgCnt = 1; DC390_ENABLE_MSGOUT;
    pSRB->pSRBDCB->DCBFlag &= ~ABORT_DEV_;
}