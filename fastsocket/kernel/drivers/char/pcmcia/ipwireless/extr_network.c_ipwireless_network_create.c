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
struct ipw_network {int /*<<< orphan*/  work_go_offline; int /*<<< orphan*/  work_go_online; struct ipw_hardware* hardware; int /*<<< orphan*/  close_lock; int /*<<< orphan*/  lock; } ;
struct ipw_hardware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_go_offline ; 
 int /*<<< orphan*/  do_go_online ; 
 int /*<<< orphan*/  ipwireless_associate_network (struct ipw_hardware*,struct ipw_network*) ; 
 struct ipw_network* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ipw_network *ipwireless_network_create(struct ipw_hardware *hw)
{
	struct ipw_network *network =
		kzalloc(sizeof(struct ipw_network), GFP_ATOMIC);

	if (!network)
		return NULL;

	spin_lock_init(&network->lock);
	mutex_init(&network->close_lock);

	network->hardware = hw;

	INIT_WORK(&network->work_go_online, do_go_online);
	INIT_WORK(&network->work_go_offline, do_go_offline);

	ipwireless_associate_network(hw, network);

	return network;
}