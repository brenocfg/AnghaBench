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

/* Variables and functions */
 int IFNAMSIZ ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static struct net_device *find_lec_by_itfnum(int itf)
{
	struct net_device *dev;
	char name[IFNAMSIZ];

	sprintf(name, "lec%d", itf);
	dev = dev_get_by_name(&init_net, name);

	return dev;
}