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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROM_CMD ; 
 int EPROM_CS_SHIFT ; 
 int /*<<< orphan*/  EPROM_DELAY ; 
 int /*<<< orphan*/  force_pci_posting (struct net_device*) ; 
 int read_nic_byte_E (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_byte_E (struct net_device*,int /*<<< orphan*/ ,int) ; 

void eprom_cs(struct net_device *dev, short bit)
{
	if(bit)
		write_nic_byte_E(dev, EPROM_CMD,
			       (1<<EPROM_CS_SHIFT) | \
			       read_nic_byte_E(dev, EPROM_CMD)); //enable EPROM
	else
		write_nic_byte_E(dev, EPROM_CMD, read_nic_byte_E(dev, EPROM_CMD)\
			       &~(1<<EPROM_CS_SHIFT)); //disable EPROM

	force_pci_posting(dev);
	udelay(EPROM_DELAY);
}