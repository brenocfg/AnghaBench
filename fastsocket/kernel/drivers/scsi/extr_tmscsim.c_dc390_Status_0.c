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
typedef  int /*<<< orphan*/  u8 ;
struct dc390_srb {int /*<<< orphan*/  SRBState; void* EndMessage; void* TargetStatus; } ;
struct dc390_acb {int dummy; } ;

/* Variables and functions */
 void* DC390_read8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC390_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSG_ACCEPTED_CMD ; 
 int /*<<< orphan*/  SCSI_NOP0 ; 
 int /*<<< orphan*/  SRB_COMPLETED ; 
 int /*<<< orphan*/  ScsiCmd ; 
 int /*<<< orphan*/  ScsiFifo ; 

__attribute__((used)) static void
dc390_Status_0( struct dc390_acb* pACB, struct dc390_srb* pSRB, u8 *psstatus)
{

    pSRB->TargetStatus = DC390_read8 (ScsiFifo);
    //udelay (1);
    pSRB->EndMessage = DC390_read8 (ScsiFifo);	/* get message */

    *psstatus = SCSI_NOP0;
    pSRB->SRBState = SRB_COMPLETED;
    DC390_write8 (ScsiCmd, MSG_ACCEPTED_CMD);
}