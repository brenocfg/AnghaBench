#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  data; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {scalar_t__ speed; int /*<<< orphan*/  duplex; int /*<<< orphan*/  port; } ;
struct TYPE_6__ {TYPE_2__ mii; TYPE_1__ link; int /*<<< orphan*/  pmt; } ;
struct mac_device_info {TYPE_3__ hw; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAC_CONTROL_F ; 
 int /*<<< orphan*/  MAC_CONTROL_PS ; 
 int /*<<< orphan*/  MAC_MII_ADDR ; 
 int /*<<< orphan*/  MAC_MII_DATA ; 
 int /*<<< orphan*/  PMT_NOT_SUPPORTED ; 
 struct mac_device_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac100_driver ; 
 int /*<<< orphan*/  pr_info (char*) ; 

struct mac_device_info *mac100_setup(unsigned long ioaddr)
{
	struct mac_device_info *mac;

	mac = kzalloc(sizeof(const struct mac_device_info), GFP_KERNEL);

	pr_info("\tMAC 10/100\n");

	mac->ops = &mac100_driver;
	mac->hw.pmt = PMT_NOT_SUPPORTED;
	mac->hw.link.port = MAC_CONTROL_PS;
	mac->hw.link.duplex = MAC_CONTROL_F;
	mac->hw.link.speed = 0;
	mac->hw.mii.addr = MAC_MII_ADDR;
	mac->hw.mii.data = MAC_MII_DATA;

	return mac;
}