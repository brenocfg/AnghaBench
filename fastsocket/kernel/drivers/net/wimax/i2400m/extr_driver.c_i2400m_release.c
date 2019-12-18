#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_3__* net_dev; } ;
struct i2400m {int /*<<< orphan*/  bm_cmd_buf; int /*<<< orphan*/  bm_ack_buf; TYPE_2__ wimax_dev; } ;
struct device {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_7__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct i2400m*) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_debugfs_rm (struct i2400m*) ; 
 struct device* i2400m_dev (struct i2400m*) ; 
 int /*<<< orphan*/  i2400m_dev_attr_group ; 
 int /*<<< orphan*/  i2400m_dev_stop (struct i2400m*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (TYPE_3__*) ; 
 int /*<<< orphan*/  wimax_dev_rm (TYPE_2__*) ; 

void i2400m_release(struct i2400m *i2400m)
{
	struct device *dev = i2400m_dev(i2400m);

	d_fnstart(3, dev, "(i2400m %p)\n", i2400m);
	netif_stop_queue(i2400m->wimax_dev.net_dev);

	i2400m_debugfs_rm(i2400m);
	sysfs_remove_group(&i2400m->wimax_dev.net_dev->dev.kobj,
			   &i2400m_dev_attr_group);
	wimax_dev_rm(&i2400m->wimax_dev);
	i2400m_dev_stop(i2400m);
	unregister_netdev(i2400m->wimax_dev.net_dev);
	kfree(i2400m->bm_ack_buf);
	kfree(i2400m->bm_cmd_buf);
	d_fnend(3, dev, "(i2400m %p) = void\n", i2400m);
}