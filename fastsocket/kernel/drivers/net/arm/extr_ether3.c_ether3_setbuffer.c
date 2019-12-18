#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ buffer_rw_t ;
struct TYPE_3__ {int config1; int command; } ;
struct TYPE_4__ {int broken; TYPE_1__ regs; } ;

/* Variables and functions */
 int CFG1_LOCBUFMEM ; 
 int CMD_FIFOREAD ; 
 int CMD_FIFOWRITE ; 
 int /*<<< orphan*/  REG_COMMAND ; 
 int /*<<< orphan*/  REG_CONFIG1 ; 
 int /*<<< orphan*/  REG_DMAADDR ; 
 int /*<<< orphan*/  REG_STATUS ; 
 int STAT_FIFOEMPTY ; 
 scalar_t__ buffer_read ; 
 int ether3_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether3_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* priv (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
ether3_setbuffer(struct net_device *dev, buffer_rw_t read, int start)
{
	int timeout = 1000;

	ether3_outw(priv(dev)->regs.config1 | CFG1_LOCBUFMEM, REG_CONFIG1);
	ether3_outw(priv(dev)->regs.command | CMD_FIFOWRITE, REG_COMMAND);

	while ((ether3_inw(REG_STATUS) & STAT_FIFOEMPTY) == 0) {
		if (!timeout--) {
			printk("%s: setbuffer broken\n", dev->name);
			priv(dev)->broken = 1;
			return 1;
		}
		udelay(1);
	}

	if (read == buffer_read) {
		ether3_outw(start, REG_DMAADDR);
		ether3_outw(priv(dev)->regs.command | CMD_FIFOREAD, REG_COMMAND);
	} else {
		ether3_outw(priv(dev)->regs.command | CMD_FIFOWRITE, REG_COMMAND);
		ether3_outw(start, REG_DMAADDR);
	}
	return 0;
}