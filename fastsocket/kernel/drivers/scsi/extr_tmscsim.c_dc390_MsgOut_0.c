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
struct dc390_srb {int SRBState; } ;
struct dc390_acb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCSI_NOP0 ; 
 int SRB_ABORT_SENT ; 
 int SRB_UNEXPECT_RESEL ; 

__attribute__((used)) static void
dc390_MsgOut_0( struct dc390_acb* pACB, struct dc390_srb* pSRB, u8 *psstatus)
{
    if( pSRB->SRBState & (SRB_UNEXPECT_RESEL+SRB_ABORT_SENT) )
	*psstatus = SCSI_NOP0;
    //DC390_write8 (DMA_Cmd, DMA_IDLE_CMD);
}