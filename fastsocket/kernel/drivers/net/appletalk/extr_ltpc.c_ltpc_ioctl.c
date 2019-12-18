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
struct TYPE_2__ {int /*<<< orphan*/  s_node; int /*<<< orphan*/  s_net; } ;
struct sockaddr_at {TYPE_1__ sat_addr; } ;
struct net_device {int* broadcast; int addr_len; int /*<<< orphan*/ * dev_addr; } ;
struct atalk_addr {int /*<<< orphan*/  s_node; int /*<<< orphan*/  s_net; } ;
struct ltpc_private {struct atalk_addr my_addr; } ;
struct lt_init {int /*<<< orphan*/  hint; int /*<<< orphan*/  command; } ;
struct ifreq {int /*<<< orphan*/  ifr_addr; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int DEBUG_VERBOSE ; 
 int EINVAL ; 
 int LT_FLAG_ALLLAP ; 
 int /*<<< orphan*/  LT_INIT ; 
#define  SIOCGIFADDR 129 
#define  SIOCSIFADDR 128 
 int debug ; 
 int /*<<< orphan*/  do_read (struct net_device*,struct lt_init*,int,struct lt_init*,int /*<<< orphan*/ ) ; 
 struct ltpc_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int read_30 (struct net_device*) ; 
 int /*<<< orphan*/  set_30 (struct net_device*,int) ; 

__attribute__((used)) static int ltpc_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	struct sockaddr_at *sa = (struct sockaddr_at *) &ifr->ifr_addr;
	/* we'll keep the localtalk node address in dev->pa_addr */
	struct ltpc_private *ltpc_priv = netdev_priv(dev);
	struct atalk_addr *aa = &ltpc_priv->my_addr;
	struct lt_init c;
	int ltflags;

	if(debug & DEBUG_VERBOSE) printk("ltpc_ioctl called\n");

	switch(cmd) {
		case SIOCSIFADDR:

			aa->s_net  = sa->sat_addr.s_net;
      
			/* this does the probe and returns the node addr */
			c.command = LT_INIT;
			c.hint = sa->sat_addr.s_node;

			aa->s_node = do_read(dev,&c,sizeof(c),&c,0);

			/* get all llap frames raw */
			ltflags = read_30(dev);
			ltflags |= LT_FLAG_ALLLAP;
			set_30 (dev,ltflags);  

			dev->broadcast[0] = 0xFF;
			dev->dev_addr[0] = aa->s_node;

			dev->addr_len=1;
   
			return 0;

		case SIOCGIFADDR:

			sa->sat_addr.s_net = aa->s_net;
			sa->sat_addr.s_node = aa->s_node;

			return 0;

		default: 
			return -EINVAL;
	}
}