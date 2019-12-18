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
typedef  int u8 ;
typedef  int /*<<< orphan*/ * u16 ;
struct net_device {struct ethtool_ops* ethtool_ops; } ;
struct ethtool_ops {int /*<<< orphan*/  (* get_eeprom ) (struct net_device*,struct ethtool_eeprom*,int*) ;int /*<<< orphan*/  (* get_eeprom_len ) (struct net_device*) ;} ;
struct ethtool_eeprom {int /*<<< orphan*/  len; scalar_t__ offset; } ;
struct e1000_adapter {struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int EEPROM_CHECKSUM_REG ; 
 int /*<<< orphan*/ * EEPROM_SUM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 
 int /*<<< orphan*/  stub2 (struct net_device*,struct ethtool_eeprom*,int*) ; 

__attribute__((used)) static void e1000_dump_eeprom(struct e1000_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct ethtool_eeprom eeprom;
	const struct ethtool_ops *ops = netdev->ethtool_ops;
	u8 *data;
	int i;
	u16 csum_old, csum_new = 0;

	eeprom.len = ops->get_eeprom_len(netdev);
	eeprom.offset = 0;

	data = kmalloc(eeprom.len, GFP_KERNEL);
	if (!data)
		return;

	ops->get_eeprom(netdev, &eeprom, data);

	csum_old = (data[EEPROM_CHECKSUM_REG * 2]) +
		   (data[EEPROM_CHECKSUM_REG * 2 + 1] << 8);
	for (i = 0; i < EEPROM_CHECKSUM_REG * 2; i += 2)
		csum_new += data[i] + (data[i + 1] << 8);
	csum_new = EEPROM_SUM - csum_new;

	pr_err("/*********************/\n");
	pr_err("Current EEPROM Checksum : 0x%04x\n", csum_old);
	pr_err("Calculated              : 0x%04x\n", csum_new);

	pr_err("Offset    Values\n");
	pr_err("========  ======\n");
	print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 16, 1, data, 128, 0);

	pr_err("Include this output when contacting your support provider.\n");
	pr_err("This is not a software error! Something bad happened to\n");
	pr_err("your hardware or EEPROM image. Ignoring this problem could\n");
	pr_err("result in further problems, possibly loss of data,\n");
	pr_err("corruption or system hangs!\n");
	pr_err("The MAC Address will be reset to 00:00:00:00:00:00,\n");
	pr_err("which is invalid and requires you to set the proper MAC\n");
	pr_err("address manually before continuing to enable this network\n");
	pr_err("device. Please inspect the EEPROM dump and report the\n");
	pr_err("issue to your hardware vendor or Intel Customer Support.\n");
	pr_err("/*********************/\n");

	kfree(data);
}