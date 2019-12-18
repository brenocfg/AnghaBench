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
struct dc390_srb {int /*<<< orphan*/  SRBState; } ;
struct dc390_acb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FIFO_CMD ; 
 int /*<<< orphan*/  DC390_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITIATOR_CMD_CMPLTE ; 
 int /*<<< orphan*/  SRB_STATUS ; 
 int /*<<< orphan*/  ScsiCmd ; 

__attribute__((used)) static void
dc390_StatusPhase( struct dc390_acb* pACB, struct dc390_srb* pSRB, u8 *psstatus)
{
    DC390_write8 (ScsiCmd, CLEAR_FIFO_CMD);
    pSRB->SRBState = SRB_STATUS;
    DC390_write8 (ScsiCmd, INITIATOR_CMD_CMPLTE);
    //DC390_write8 (DMA_Cmd, DMA_IDLE_CMD);
}