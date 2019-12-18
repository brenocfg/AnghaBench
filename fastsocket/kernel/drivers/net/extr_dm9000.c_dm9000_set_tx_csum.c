#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ can_csum; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int ethtool_op_set_tx_csum (struct net_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static int dm9000_set_tx_csum(struct net_device *dev, uint32_t data)
{
	board_info_t *dm = to_dm9000_board(dev);
	int ret = -EOPNOTSUPP;

	if (dm->can_csum)
		ret = ethtool_op_set_tx_csum(dev, data);
	return ret;
}