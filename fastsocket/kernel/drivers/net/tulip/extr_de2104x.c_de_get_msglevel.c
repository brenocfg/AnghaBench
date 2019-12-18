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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct de_private {int /*<<< orphan*/  msg_enable; } ;

/* Variables and functions */
 struct de_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 de_get_msglevel(struct net_device *dev)
{
	struct de_private *de = netdev_priv(dev);

	return de->msg_enable;
}