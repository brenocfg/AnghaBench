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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device_context {struct hv_device* device_ctx; } ;
struct net_device {char* dev_addr; unsigned char addr_assign_type; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int eth_mac_addr (struct net_device*,void*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int rndis_filter_set_device_mac (struct hv_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_set_mac_addr(struct net_device *ndev, void *p)
{
	struct net_device_context *ndevctx = netdev_priv(ndev);
	struct hv_device *hdev =  ndevctx->device_ctx;
	struct sockaddr *addr = p;
	char save_adr[ETH_ALEN];
	unsigned char save_aatype;
	int err;

	memcpy(save_adr, ndev->dev_addr, ETH_ALEN);
	save_aatype = ndev->addr_assign_type;

	err = eth_mac_addr(ndev, p);
	if (err != 0)
		return err;

	err = rndis_filter_set_device_mac(hdev, addr->sa_data);
	if (err != 0) {
		/* roll back to saved MAC */
		memcpy(ndev->dev_addr, save_adr, ETH_ALEN);
		ndev->addr_assign_type = save_aatype;
	}

	return err;
}