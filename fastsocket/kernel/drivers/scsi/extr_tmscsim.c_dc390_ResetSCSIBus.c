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
struct dc390_acb {scalar_t__ Connected; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_FIFO_CMD ; 
 int /*<<< orphan*/  DC390_write8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_Cmd ; 
 int /*<<< orphan*/  DMA_IDLE_CMD ; 
 int /*<<< orphan*/  RST_SCSI_BUS_CMD ; 
 int /*<<< orphan*/  ScsiCmd ; 

__attribute__((used)) static void
dc390_ResetSCSIBus( struct dc390_acb* pACB )
{
    //DC390_write8 (ScsiCmd, RST_DEVICE_CMD);
    //udelay (250);
    //DC390_write8 (ScsiCmd, NOP_CMD);

    DC390_write8 (ScsiCmd, CLEAR_FIFO_CMD);
    DC390_write8 (DMA_Cmd, DMA_IDLE_CMD);
    DC390_write8 (ScsiCmd, RST_SCSI_BUS_CMD);
    pACB->Connected = 0;

    return;
}