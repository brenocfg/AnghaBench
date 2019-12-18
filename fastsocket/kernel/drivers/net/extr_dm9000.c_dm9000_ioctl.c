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
struct ifreq {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  mii; } ;
typedef  TYPE_1__ board_info_t ;

/* Variables and functions */
 int EINVAL ; 
 int generic_mii_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 TYPE_1__* to_dm9000_board (struct net_device*) ; 

__attribute__((used)) static int dm9000_ioctl(struct net_device *dev, struct ifreq *req, int cmd)
{
	board_info_t *dm = to_dm9000_board(dev);

	if (!netif_running(dev))
		return -EINVAL;

	return generic_mii_ioctl(&dm->mii, if_mii(req), cmd, NULL);
}