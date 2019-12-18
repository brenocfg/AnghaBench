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
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct ethtool_flash {char* data; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,char*) ; 
 struct adapter* netdev2adap (struct net_device*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int t4_load_fw (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_flash(struct net_device *netdev, struct ethtool_flash *ef)
{
	int ret;
	const struct firmware *fw;
	struct adapter *adap = netdev2adap(netdev);

	ef->data[sizeof(ef->data) - 1] = '\0';
	ret = request_firmware(&fw, ef->data, adap->pdev_dev);
	if (ret < 0)
		return ret;

	ret = t4_load_fw(adap, fw->data, fw->size);
	release_firmware(fw);
	if (!ret)
		dev_info(adap->pdev_dev, "loaded firmware %s\n", ef->data);
	return ret;
}