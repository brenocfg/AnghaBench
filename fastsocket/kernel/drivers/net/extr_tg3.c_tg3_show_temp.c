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
typedef  int /*<<< orphan*/  temperature ;
struct tg3 {int /*<<< orphan*/  lock; } ;
struct sensor_device_attribute {int /*<<< orphan*/  index; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 struct tg3* netdev_priv (struct net_device*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  tg3_ape_scratchpad_read (struct tg3*,int*,int /*<<< orphan*/ ,int) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t tg3_show_temp(struct device *dev,
			     struct device_attribute *devattr, char *buf)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct tg3 *tp = netdev_priv(netdev);
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	u32 temperature;

	spin_lock_bh(&tp->lock);
	tg3_ape_scratchpad_read(tp, &temperature, attr->index,
				sizeof(temperature));
	spin_unlock_bh(&tp->lock);
	return sprintf(buf, "%u\n", temperature);
}