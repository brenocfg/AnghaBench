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
typedef  int /*<<< orphan*/  u32 ;
struct virtio_net_config {int /*<<< orphan*/  mac; } ;
struct net_info {int /*<<< orphan*/  tunfd; } ;
struct device {struct net_info* priv; } ;
typedef  int /*<<< orphan*/  conf ;
struct TYPE_2__ {int /*<<< orphan*/  device_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_PFX ; 
 int IFNAMSIZ ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_IP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  VIRTIO_F_NOTIFY_ON_EMPTY ; 
 int /*<<< orphan*/  VIRTIO_ID_NET ; 
 int /*<<< orphan*/  VIRTIO_NET_F_CSUM ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_CSUM ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_ECN ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_TSO4 ; 
 int /*<<< orphan*/  VIRTIO_NET_F_GUEST_TSO6 ; 
 int /*<<< orphan*/  VIRTIO_NET_F_HOST_ECN ; 
 int /*<<< orphan*/  VIRTIO_NET_F_HOST_TSO4 ; 
 int /*<<< orphan*/  VIRTIO_NET_F_HOST_TSO6 ; 
 int /*<<< orphan*/  VIRTIO_NET_F_MAC ; 
 int /*<<< orphan*/  VIRTIO_RING_F_INDIRECT_DESC ; 
 int /*<<< orphan*/  VIRTQUEUE_NUM ; 
 int /*<<< orphan*/  add_feature (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_to_bridge (int,char*,char*) ; 
 int /*<<< orphan*/  add_virtqueue (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  configure_device (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__ devices ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  get_tun_device (char*) ; 
 struct net_info* malloc (int) ; 
 int /*<<< orphan*/  net_input ; 
 int /*<<< orphan*/  net_output ; 
 struct device* new_device (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_config (struct device*,int,struct virtio_net_config*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str2ip (char*) ; 
 int /*<<< orphan*/  str2mac (char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (char*,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void setup_tun_net(char *arg)
{
	struct device *dev;
	struct net_info *net_info = malloc(sizeof(*net_info));
	int ipfd;
	u32 ip = INADDR_ANY;
	bool bridging = false;
	char tapif[IFNAMSIZ], *p;
	struct virtio_net_config conf;

	net_info->tunfd = get_tun_device(tapif);

	/* First we create a new network device. */
	dev = new_device("net", VIRTIO_ID_NET);
	dev->priv = net_info;

	/* Network devices need a recv and a send queue, just like console. */
	add_virtqueue(dev, VIRTQUEUE_NUM, net_input);
	add_virtqueue(dev, VIRTQUEUE_NUM, net_output);

	/*
	 * We need a socket to perform the magic network ioctls to bring up the
	 * tap interface, connect to the bridge etc.  Any socket will do!
	 */
	ipfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
	if (ipfd < 0)
		err(1, "opening IP socket");

	/* If the command line was --tunnet=bridge:<name> do bridging. */
	if (!strncmp(BRIDGE_PFX, arg, strlen(BRIDGE_PFX))) {
		arg += strlen(BRIDGE_PFX);
		bridging = true;
	}

	/* A mac address may follow the bridge name or IP address */
	p = strchr(arg, ':');
	if (p) {
		str2mac(p+1, conf.mac);
		add_feature(dev, VIRTIO_NET_F_MAC);
		*p = '\0';
	}

	/* arg is now either an IP address or a bridge name */
	if (bridging)
		add_to_bridge(ipfd, tapif, arg);
	else
		ip = str2ip(arg);

	/* Set up the tun device. */
	configure_device(ipfd, tapif, ip);

	add_feature(dev, VIRTIO_F_NOTIFY_ON_EMPTY);
	/* Expect Guest to handle everything except UFO */
	add_feature(dev, VIRTIO_NET_F_CSUM);
	add_feature(dev, VIRTIO_NET_F_GUEST_CSUM);
	add_feature(dev, VIRTIO_NET_F_GUEST_TSO4);
	add_feature(dev, VIRTIO_NET_F_GUEST_TSO6);
	add_feature(dev, VIRTIO_NET_F_GUEST_ECN);
	add_feature(dev, VIRTIO_NET_F_HOST_TSO4);
	add_feature(dev, VIRTIO_NET_F_HOST_TSO6);
	add_feature(dev, VIRTIO_NET_F_HOST_ECN);
	/* We handle indirect ring entries */
	add_feature(dev, VIRTIO_RING_F_INDIRECT_DESC);
	set_config(dev, sizeof(conf), &conf);

	/* We don't need the socket any more; setup is done. */
	close(ipfd);

	devices.device_num++;

	if (bridging)
		verbose("device %u: tun %s attached to bridge: %s\n",
			devices.device_num, tapif, arg);
	else
		verbose("device %u: tun %s: %s\n",
			devices.device_num, tapif, arg);
}