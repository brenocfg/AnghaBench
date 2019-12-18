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
struct sit_net {struct ip_tunnel*** tunnels; } ;
struct ip_tunnel {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HASH_SIZE ; 
 int /*<<< orphan*/  unregister_netdevice (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sit_destroy_tunnels(struct sit_net *sitn)
{
	int prio;

	for (prio = 1; prio < 4; prio++) {
		int h;
		for (h = 0; h < HASH_SIZE; h++) {
			struct ip_tunnel *t;
			while ((t = sitn->tunnels[prio][h]) != NULL)
				unregister_netdevice(t->dev);
		}
	}
}