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
typedef  scalar_t__ u64 ;
struct config_param {int max_mc_addr; } ;
struct s2io_nic {struct config_param config; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S2IO_DISABLE_MAC_ENTRY ; 
 int /*<<< orphan*/  do_s2io_delete_unicast_mc (struct s2io_nic*,scalar_t__) ; 
 scalar_t__ do_s2io_read_unicast_mc (struct s2io_nic*,int) ; 
 int /*<<< orphan*/  is_s2io_card_up (struct s2io_nic*) ; 
 struct s2io_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  s2io_card_down (struct s2io_nic*) ; 
 int /*<<< orphan*/  s2io_stop_all_tx_queue (struct s2io_nic*) ; 

__attribute__((used)) static int s2io_close(struct net_device *dev)
{
	struct s2io_nic *sp = netdev_priv(dev);
	struct config_param *config = &sp->config;
	u64 tmp64;
	int offset;

	/* Return if the device is already closed               *
	 *  Can happen when s2io_card_up failed in change_mtu    *
	 */
	if (!is_s2io_card_up(sp))
		return 0;

	s2io_stop_all_tx_queue(sp);
	/* delete all populated mac entries */
	for (offset = 1; offset < config->max_mc_addr; offset++) {
		tmp64 = do_s2io_read_unicast_mc(sp, offset);
		if (tmp64 != S2IO_DISABLE_MAC_ENTRY)
			do_s2io_delete_unicast_mc(sp, tmp64);
	}

	s2io_card_down(sp);

	return 0;
}