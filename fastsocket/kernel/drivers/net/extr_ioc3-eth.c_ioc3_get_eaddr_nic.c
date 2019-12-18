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
typedef  int /*<<< orphan*/  u8 ;
struct ioc3_private {struct ioc3* regs; } ;
struct ioc3 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ioc3_w_gpcr_s (int) ; 
 int /*<<< orphan*/  nic_init (struct ioc3*) ; 
 int /*<<< orphan*/  nic_read_byte (struct ioc3*) ; 
 int /*<<< orphan*/  nic_write_byte (struct ioc3*,int) ; 
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* priv_netdev (struct ioc3_private*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ioc3_get_eaddr_nic(struct ioc3_private *ip)
{
	struct ioc3 *ioc3 = ip->regs;
	u8 nic[14];
	int tries = 2; /* There may be some problem with the battery?  */
	int i;

	ioc3_w_gpcr_s(1 << 21);

	while (tries--) {
		if (!nic_init(ioc3))
			break;
		udelay(500);
	}

	if (tries < 0) {
		printk("Failed to read MAC address\n");
		return;
	}

	/* Read Memory.  */
	nic_write_byte(ioc3, 0xf0);
	nic_write_byte(ioc3, 0x00);
	nic_write_byte(ioc3, 0x00);

	for (i = 13; i >= 0; i--)
		nic[i] = nic_read_byte(ioc3);

	for (i = 2; i < 8; i++)
		priv_netdev(ip)->dev_addr[i - 2] = nic[i];
}