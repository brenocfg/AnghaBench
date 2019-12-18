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
typedef  int u32 ;
struct temac_option {int opt; int m_or; int /*<<< orphan*/  reg; } ;
struct temac_local {int options; int /*<<< orphan*/  indirect_mutex; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 int temac_indirect_in32 (struct temac_local*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  temac_indirect_out32 (struct temac_local*,int /*<<< orphan*/ ,int) ; 
 struct temac_option* temac_options ; 

__attribute__((used)) static u32 temac_setoptions(struct net_device *ndev, u32 options)
{
	struct temac_local *lp = netdev_priv(ndev);
	struct temac_option *tp = &temac_options[0];
	int reg;

	mutex_lock(&lp->indirect_mutex);
	while (tp->opt) {
		reg = temac_indirect_in32(lp, tp->reg) & ~tp->m_or;
		if (options & tp->opt)
			reg |= tp->m_or;
		temac_indirect_out32(lp, tp->reg, reg);
		tp++;
	}
	lp->options |= options;
	mutex_unlock(&lp->indirect_mutex);

	return (0);
}