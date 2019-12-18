#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  sk; } ;
struct tun_struct {TYPE_1__ socket; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct tun_struct* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  sock_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tun_free_netdev(struct net_device *dev)
{
	struct tun_struct *tun = netdev_priv(dev);

	sock_put(tun->socket.sk);
}