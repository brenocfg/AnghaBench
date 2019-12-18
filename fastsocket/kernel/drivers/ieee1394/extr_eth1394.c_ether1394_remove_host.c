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
struct hpsb_host {int dummy; } ;
struct eth1394_priv {scalar_t__ iso; int /*<<< orphan*/  local_fifo; } ;
struct eth1394_host_info {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth1394_highlevel ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hpsb_config_rom_ip1394_remove (struct hpsb_host*) ; 
 struct eth1394_host_info* hpsb_get_hostinfo (int /*<<< orphan*/ *,struct hpsb_host*) ; 
 int /*<<< orphan*/  hpsb_iso_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  hpsb_unregister_addrspace (int /*<<< orphan*/ *,struct hpsb_host*,int /*<<< orphan*/ ) ; 
 struct eth1394_priv* netdev_priv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ether1394_remove_host(struct hpsb_host *host)
{
	struct eth1394_host_info *hi;
	struct eth1394_priv *priv;

	hi = hpsb_get_hostinfo(&eth1394_highlevel, host);
	if (!hi)
		return;
	priv = netdev_priv(hi->dev);
	hpsb_unregister_addrspace(&eth1394_highlevel, host, priv->local_fifo);
	hpsb_config_rom_ip1394_remove(host);
	if (priv->iso)
		hpsb_iso_shutdown(priv->iso);
	unregister_netdev(hi->dev);
	free_netdev(hi->dev);
}