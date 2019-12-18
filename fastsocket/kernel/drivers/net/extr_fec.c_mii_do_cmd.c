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
struct TYPE_3__ {scalar_t__ mii_data; int /*<<< orphan*/  funct; } ;
typedef  TYPE_1__ phy_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  mii_queue (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ mk_mii_end ; 

__attribute__((used)) static void mii_do_cmd(struct net_device *dev, const phy_cmd_t *c)
{
	if(!c)
		return;

	for (; c->mii_data != mk_mii_end; c++)
		mii_queue(dev, c->mii_data, c->funct);
}