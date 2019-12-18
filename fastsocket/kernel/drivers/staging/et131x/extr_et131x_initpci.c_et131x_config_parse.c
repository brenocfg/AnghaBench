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
typedef  int u8 ;
typedef  int u16 ;
struct et131x_adapter {int SpeedDuplex; int RegistryJumboPacket; int AiForceSpeed; int AiForceDpx; TYPE_1__* pdev; int /*<<< orphan*/  CurrentAddress; int /*<<< orphan*/  RegistryNMIDisable; } ;
struct TYPE_2__ {scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ET131X_PCI_DEVICE_ID_FAST ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  et131x_nmi_disable ; 
 int et131x_speed_set ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ ) ; 

void et131x_config_parse(struct et131x_adapter *etdev)
{
	static const u8 default_mac[] = { 0x00, 0x05, 0x3d, 0x00, 0x02, 0x00 };
	static const u8 duplex[] = { 0, 1, 2, 1, 2, 2 };
	static const u16 speed[] = { 0, 10, 10, 100, 100, 1000 };

	if (et131x_speed_set)
		dev_info(&etdev->pdev->dev,
			"Speed set manually to : %d \n", et131x_speed_set);

	etdev->SpeedDuplex = et131x_speed_set;
	etdev->RegistryJumboPacket = 1514;	/* 1514-9216 */

	etdev->RegistryNMIDisable = et131x_nmi_disable;

	/* Set the MAC address to a default */
	memcpy(etdev->CurrentAddress, default_mac, ETH_ALEN);

	/* Decode SpeedDuplex
	 *
	 * Set up as if we are auto negotiating always and then change if we
	 * go into force mode
	 *
	 * If we are the 10/100 device, and gigabit is somehow requested then
	 * knock it down to 100 full.
	 */
	if (etdev->pdev->device == ET131X_PCI_DEVICE_ID_FAST &&
	    etdev->SpeedDuplex == 5)
		etdev->SpeedDuplex = 4;

	etdev->AiForceSpeed = speed[etdev->SpeedDuplex];
	etdev->AiForceDpx = duplex[etdev->SpeedDuplex];	/* Auto FDX */
}