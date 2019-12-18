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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct mace_data {scalar_t__ rx_tail; scalar_t__ rx_ring_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  N_RX_RING ; 
 scalar_t__ PSC_ENETRD_ADDR ; 
 scalar_t__ PSC_ENETRD_CMD ; 
 scalar_t__ PSC_ENETRD_LEN ; 
 struct mace_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  psc_write_long (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psc_write_word (scalar_t__,int) ; 

__attribute__((used)) static void mace_load_rxdma_base(struct net_device *dev, int set)
{
	struct mace_data *mp = netdev_priv(dev);

	psc_write_word(PSC_ENETRD_CMD + set, 0x0100);
	psc_write_long(PSC_ENETRD_ADDR + set, (u32) mp->rx_ring_phys);
	psc_write_long(PSC_ENETRD_LEN + set, N_RX_RING);
	psc_write_word(PSC_ENETRD_CMD + set, 0x9800);
	mp->rx_tail = 0;
}