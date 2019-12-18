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
struct net_device {int dummy; } ;
struct ethtool_cmd {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mii; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int mii_ethtool_sset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 TYPE_1__* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static int dm9000_set_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	board_info_t *dm = to_dm9000_board(dev);

	return mii_ethtool_sset(&dm->mii, cmd);
}