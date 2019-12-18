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
typedef  int /*<<< orphan*/  u8 ;
struct ql_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  ndev; } ;
struct net_device {int flags; scalar_t__ mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {scalar_t__ dmi_addr; struct dev_mc_list* next; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MAC_ADDR_TYPE_MULTI_MAC ; 
 scalar_t__ MAX_MULTICAST_ENTRIES ; 
 int /*<<< orphan*/  QL_ALLMULTI ; 
 int /*<<< orphan*/  QL_PROMISCUOUS ; 
 int /*<<< orphan*/  RT_IDX_ALLMULTI_SLOT ; 
 int /*<<< orphan*/  RT_IDX_MCAST ; 
 int /*<<< orphan*/  RT_IDX_MCAST_MATCH ; 
 int /*<<< orphan*/  RT_IDX_MCAST_MATCH_SLOT ; 
 int /*<<< orphan*/  RT_IDX_PROMISCUOUS_SLOT ; 
 int /*<<< orphan*/  RT_IDX_VALID ; 
 int /*<<< orphan*/  SEM_MAC_ADDR_MASK ; 
 int /*<<< orphan*/  SEM_RT_IDX_MASK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hw ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ql_sem_spinlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_sem_unlock (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ ql_set_mac_addr_reg (struct ql_adapter*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ql_set_routing_reg (struct ql_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlge_set_multicast_list(struct net_device *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	struct dev_mc_list *mc_ptr;
	int i, status;

	status = ql_sem_spinlock(qdev, SEM_RT_IDX_MASK);
	if (status)
		return;
	/*
	 * Set or clear promiscuous mode if a
	 * transition is taking place.
	 */
	if (ndev->flags & IFF_PROMISC) {
		if (!test_bit(QL_PROMISCUOUS, &qdev->flags)) {
			if (ql_set_routing_reg
			    (qdev, RT_IDX_PROMISCUOUS_SLOT, RT_IDX_VALID, 1)) {
				netif_err(qdev, hw, qdev->ndev,
					  "Failed to set promiscous mode.\n");
			} else {
				set_bit(QL_PROMISCUOUS, &qdev->flags);
			}
		}
	} else {
		if (test_bit(QL_PROMISCUOUS, &qdev->flags)) {
			if (ql_set_routing_reg
			    (qdev, RT_IDX_PROMISCUOUS_SLOT, RT_IDX_VALID, 0)) {
				netif_err(qdev, hw, qdev->ndev,
					  "Failed to clear promiscous mode.\n");
			} else {
				clear_bit(QL_PROMISCUOUS, &qdev->flags);
			}
		}
	}

	/*
	 * Set or clear all multicast mode if a
	 * transition is taking place.
	 */
	if ((ndev->flags & IFF_ALLMULTI) ||
	    (ndev->mc_count > MAX_MULTICAST_ENTRIES)) {
		if (!test_bit(QL_ALLMULTI, &qdev->flags)) {
			if (ql_set_routing_reg
			    (qdev, RT_IDX_ALLMULTI_SLOT, RT_IDX_MCAST, 1)) {
				netif_err(qdev, hw, qdev->ndev,
					  "Failed to set all-multi mode.\n");
			} else {
				set_bit(QL_ALLMULTI, &qdev->flags);
			}
		}
	} else {
		if (test_bit(QL_ALLMULTI, &qdev->flags)) {
			if (ql_set_routing_reg
			    (qdev, RT_IDX_ALLMULTI_SLOT, RT_IDX_MCAST, 0)) {
				netif_err(qdev, hw, qdev->ndev,
					  "Failed to clear all-multi mode.\n");
			} else {
				clear_bit(QL_ALLMULTI, &qdev->flags);
			}
		}
	}

	if (ndev->mc_count) {
		status = ql_sem_spinlock(qdev, SEM_MAC_ADDR_MASK);
		if (status)
			goto exit;
		for (i = 0, mc_ptr = ndev->mc_list; mc_ptr;
		     i++, mc_ptr = mc_ptr->next)
			if (ql_set_mac_addr_reg(qdev, (u8 *) mc_ptr->dmi_addr,
						MAC_ADDR_TYPE_MULTI_MAC, i)) {
				netif_err(qdev, hw, qdev->ndev,
					  "Failed to loadmulticast address.\n");
				ql_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
				goto exit;
			}
		ql_sem_unlock(qdev, SEM_MAC_ADDR_MASK);
		if (ql_set_routing_reg
		    (qdev, RT_IDX_MCAST_MATCH_SLOT, RT_IDX_MCAST_MATCH, 1)) {
			netif_err(qdev, hw, qdev->ndev,
				  "Failed to set multicast match mode.\n");
		} else {
			set_bit(QL_ALLMULTI, &qdev->flags);
		}
	}
exit:
	ql_sem_unlock(qdev, SEM_RT_IDX_MASK);
}