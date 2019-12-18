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
typedef  int u32 ;
struct vxgedev {int /*<<< orphan*/  pdev; } ;
struct net_device {int dummy; } ;
struct __vxge_hw_device {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  VXGE_FLICKER_OFF ; 
 int /*<<< orphan*/  VXGE_FLICKER_ON ; 
 int VXGE_MAX_FLICKER_TIME ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 scalar_t__ netdev_priv (struct net_device*) ; 
 scalar_t__ pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vxge_hw_device_flick_link_led (struct __vxge_hw_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vxge_ethtool_idnic(struct net_device *dev, u32 data)
{
	struct vxgedev *vdev = (struct vxgedev *)netdev_priv(dev);
	struct __vxge_hw_device  *hldev = (struct __vxge_hw_device  *)
			pci_get_drvdata(vdev->pdev);

	vxge_hw_device_flick_link_led(hldev, VXGE_FLICKER_ON);
	msleep_interruptible(data ? (data * HZ) : VXGE_MAX_FLICKER_TIME);
	vxge_hw_device_flick_link_led(hldev, VXGE_FLICKER_OFF);

	return 0;
}