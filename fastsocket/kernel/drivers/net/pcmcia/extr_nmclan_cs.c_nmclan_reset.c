#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct pcmcia_device {int dummy; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_7__ {void* tx_free_frames; struct pcmcia_device link; } ;
typedef  TYPE_1__ mace_private ;
struct TYPE_8__ {int Value; void* Offset; int /*<<< orphan*/  Action; scalar_t__ Function; } ;
typedef  TYPE_2__ conf_reg_t ;

/* Variables and functions */
 void* AM2150_MAX_TX_FRAMES ; 
 void* CISREG_COR ; 
 int COR_CONFIG_MASK ; 
 int COR_LEVEL_REQ ; 
 int COR_SOFT_RESET ; 
 int /*<<< orphan*/  CS_READ ; 
 int /*<<< orphan*/  CS_WRITE ; 
 int /*<<< orphan*/  DEBUG (int,char*,int) ; 
 int /*<<< orphan*/  MACE_IMR ; 
 int /*<<< orphan*/  MACE_IMR_DEFAULT ; 
 int /*<<< orphan*/  mace_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mace_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pcmcia_access_configuration_register (struct pcmcia_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  restore_multicast_list (struct net_device*) ; 

__attribute__((used)) static void nmclan_reset(struct net_device *dev)
{
  mace_private *lp = netdev_priv(dev);

#if RESET_XILINX
  struct pcmcia_device *link = &lp->link;
  conf_reg_t reg;
  u_long OrigCorValue; 

  /* Save original COR value */
  reg.Function = 0;
  reg.Action = CS_READ;
  reg.Offset = CISREG_COR;
  reg.Value = 0;
  pcmcia_access_configuration_register(link, &reg);
  OrigCorValue = reg.Value;

  /* Reset Xilinx */
  reg.Action = CS_WRITE;
  reg.Offset = CISREG_COR;
  DEBUG(1, "nmclan_reset: OrigCorValue=0x%lX, resetting...\n",
	OrigCorValue);
  reg.Value = COR_SOFT_RESET;
  pcmcia_access_configuration_register(link, &reg);
  /* Need to wait for 20 ms for PCMCIA to finish reset. */

  /* Restore original COR configuration index */
  reg.Value = COR_LEVEL_REQ | (OrigCorValue & COR_CONFIG_MASK);
  pcmcia_access_configuration_register(link, &reg);
  /* Xilinx is now completely reset along with the MACE chip. */
  lp->tx_free_frames=AM2150_MAX_TX_FRAMES;

#endif /* #if RESET_XILINX */

  /* Xilinx is now completely reset along with the MACE chip. */
  lp->tx_free_frames=AM2150_MAX_TX_FRAMES;

  /* Reinitialize the MACE chip for operation. */
  mace_init(lp, dev->base_addr, dev->dev_addr);
  mace_write(lp, dev->base_addr, MACE_IMR, MACE_IMR_DEFAULT);

  /* Restore the multicast list and enable TX and RX. */
  restore_multicast_list(dev);
}