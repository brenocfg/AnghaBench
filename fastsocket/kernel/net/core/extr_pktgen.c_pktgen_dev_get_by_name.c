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
struct pktgen_dev {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int IFNAMSIZ ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  init_net ; 

__attribute__((used)) static struct net_device *pktgen_dev_get_by_name(struct pktgen_dev *pkt_dev,
						 const char *ifname)
{
	char b[IFNAMSIZ+5];
	int i = 0;

	for (i = 0; ifname[i] != '@'; i++) {
		if (i == IFNAMSIZ)
			break;

		b[i] = ifname[i];
	}
	b[i] = 0;

	return dev_get_by_name(&init_net, b);
}