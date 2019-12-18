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
struct s6gmac {scalar_t__ reg; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ S6_GMAC_MACCONF1 ; 
 struct s6gmac* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void s6gmac_stop_device(struct net_device *dev)
{
	struct s6gmac *pd = netdev_priv(dev);
	writel(0, pd->reg + S6_GMAC_MACCONF1);
}