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
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 

inline void force_pci_posting(struct net_device *dev)
{
	read_nic_byte(dev,EPROM_CMD);
	mb();
}