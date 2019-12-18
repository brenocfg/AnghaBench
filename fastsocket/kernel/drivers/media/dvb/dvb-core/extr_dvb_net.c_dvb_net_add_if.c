#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  void* u16 ;
struct net_device {int addr_len; int /*<<< orphan*/  name; void* base_addr; int /*<<< orphan*/  dev_addr; } ;
struct dvb_net_priv {int need_pusi; int /*<<< orphan*/  mutex; int /*<<< orphan*/  restart_net_feed_wq; int /*<<< orphan*/  set_multicast_list_wq; scalar_t__ feedtype; scalar_t__ tscc; int /*<<< orphan*/  rx_mode; void* pid; int /*<<< orphan*/  demux; struct net_device* net; } ;
struct dvb_net {struct net_device** device; int /*<<< orphan*/  demux; TYPE_2__* dvbdev; } ;
struct TYPE_4__ {int id; TYPE_1__* adapter; } ;
struct TYPE_3__ {int num; int /*<<< orphan*/  proposed_mac; } ;

/* Variables and functions */
 scalar_t__ DVB_NET_FEEDTYPE_MPE ; 
 scalar_t__ DVB_NET_FEEDTYPE_ULE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IFNAMSIZ ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RX_MODE_UNI ; 
 struct net_device* alloc_netdev (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_net_setup ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int get_if (struct dvb_net*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  reset_ule (struct dvb_net_priv*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  wq_restart_net_feed ; 
 int /*<<< orphan*/  wq_set_multicast_list ; 

__attribute__((used)) static int dvb_net_add_if(struct dvb_net *dvbnet, u16 pid, u8 feedtype)
{
	struct net_device *net;
	struct dvb_net_priv *priv;
	int result;
	int if_num;

	if (feedtype != DVB_NET_FEEDTYPE_MPE && feedtype != DVB_NET_FEEDTYPE_ULE)
		return -EINVAL;
	if ((if_num = get_if(dvbnet)) < 0)
		return -EINVAL;

	net = alloc_netdev(sizeof(struct dvb_net_priv), "dvb", dvb_net_setup);
	if (!net)
		return -ENOMEM;

	if (dvbnet->dvbdev->id)
		snprintf(net->name, IFNAMSIZ, "dvb%d%u%d",
			 dvbnet->dvbdev->adapter->num, dvbnet->dvbdev->id, if_num);
	else
		/* compatibility fix to keep dvb0_0 format */
		snprintf(net->name, IFNAMSIZ, "dvb%d_%d",
			 dvbnet->dvbdev->adapter->num, if_num);

	net->addr_len = 6;
	memcpy(net->dev_addr, dvbnet->dvbdev->adapter->proposed_mac, 6);

	dvbnet->device[if_num] = net;

	priv = netdev_priv(net);
	priv->net = net;
	priv->demux = dvbnet->demux;
	priv->pid = pid;
	priv->rx_mode = RX_MODE_UNI;
	priv->need_pusi = 1;
	priv->tscc = 0;
	priv->feedtype = feedtype;
	reset_ule(priv);

	INIT_WORK(&priv->set_multicast_list_wq, wq_set_multicast_list);
	INIT_WORK(&priv->restart_net_feed_wq, wq_restart_net_feed);
	mutex_init(&priv->mutex);

	net->base_addr = pid;

	if ((result = register_netdev(net)) < 0) {
		dvbnet->device[if_num] = NULL;
		free_netdev(net);
		return result;
	}
	printk("dvb_net: created network interface %s\n", net->name);

	return if_num;
}