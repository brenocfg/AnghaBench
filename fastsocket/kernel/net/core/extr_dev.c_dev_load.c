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
struct net_device {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int /*<<< orphan*/  CAP_SYS_MODULE ; 
 struct net_device* __dev_get_by_name (struct net*,char const*) ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_base_lock ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int request_module (char*,char const*) ; 

void dev_load(struct net *net, const char *name)
{
	struct net_device *dev;
	int no_module;

	read_lock(&dev_base_lock);
	dev = __dev_get_by_name(net, name);
	read_unlock(&dev_base_lock);

	no_module = !dev;
	if (no_module && capable(CAP_NET_ADMIN))
		no_module = request_module("netdev-%s", name);
	if (no_module && capable(CAP_SYS_MODULE)) {
		if (!request_module("%s", name))
			pr_err("Loading kernel module for a network device "
"with CAP_SYS_MODULE (deprecated).  Use CAP_NET_ADMIN and alias netdev-%s "
"instead\n", name);
	}
}