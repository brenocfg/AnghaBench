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
struct net_device {char* name; } ;

/* Variables and functions */
 struct net_device* __dev_get_by_index (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_base_lock ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static char *bcm_proc_getifname(char *result, int ifindex)
{
	struct net_device *dev;

	if (!ifindex)
		return "any";

	read_lock(&dev_base_lock);
	dev = __dev_get_by_index(&init_net, ifindex);
	if (dev)
		strcpy(result, dev->name);
	else
		strcpy(result, "???");
	read_unlock(&dev_base_lock);

	return result;
}