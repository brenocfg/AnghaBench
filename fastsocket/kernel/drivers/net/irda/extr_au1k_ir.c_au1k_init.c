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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct au1k_private {TYPE_1__** rx_ring; scalar_t__ rx_head; scalar_t__ tx_tail; scalar_t__ tx_head; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU_OWN ; 
 int /*<<< orphan*/  IR_CONFIG_2 ; 
 int /*<<< orphan*/  IR_ENABLE ; 
 int /*<<< orphan*/  IR_INTERFACE_CONFIG ; 
 int /*<<< orphan*/  IR_MAX_PKT_LEN ; 
 int IR_ONE_PIN ; 
 int /*<<< orphan*/  IR_RING_ADDR_CMPR ; 
 int /*<<< orphan*/  IR_RING_BASE_ADDR_H ; 
 int /*<<< orphan*/  IR_RING_BASE_ADDR_L ; 
 int /*<<< orphan*/  IR_RING_SIZE ; 
 int MAX_BUF_SIZE ; 
 int NUM_IR_DESC ; 
 int RING_SIZE_64 ; 
 int /*<<< orphan*/  au1k_irda_set_speed (struct net_device*,int) ; 
 int /*<<< orphan*/  au_sync_delay (int) ; 
 struct au1k_private* netdev_priv (struct net_device*) ; 
 int read_ir_reg (int /*<<< orphan*/ ) ; 
 scalar_t__ virt_to_phys (void*) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1k_init(struct net_device *dev)
{
	struct au1k_private *aup = netdev_priv(dev);
	int i;
	u32 control;
	u32 ring_address;

	/* bring the device out of reset */
	control = 0xe; /* coherent, clock enable, one half system clock */
			  
#ifndef CONFIG_CPU_LITTLE_ENDIAN
	control |= 1;
#endif
	aup->tx_head = 0;
	aup->tx_tail = 0;
	aup->rx_head = 0;

	for (i=0; i<NUM_IR_DESC; i++) {
		aup->rx_ring[i]->flags = AU_OWN;
	}

	writel(control, IR_INTERFACE_CONFIG);
	au_sync_delay(10);

	writel(read_ir_reg(IR_ENABLE) & ~0x8000, IR_ENABLE); /* disable PHY */
	au_sync_delay(1);

	writel(MAX_BUF_SIZE, IR_MAX_PKT_LEN);

	ring_address = (u32)virt_to_phys((void *)aup->rx_ring[0]);
	writel(ring_address >> 26, IR_RING_BASE_ADDR_H);
	writel((ring_address >> 10) & 0xffff, IR_RING_BASE_ADDR_L);

	writel(RING_SIZE_64<<8 | RING_SIZE_64<<12, IR_RING_SIZE);

	writel(1<<2 | IR_ONE_PIN, IR_CONFIG_2); /* 48MHz */
	writel(0, IR_RING_ADDR_CMPR);

	au1k_irda_set_speed(dev, 9600);
	return 0;
}