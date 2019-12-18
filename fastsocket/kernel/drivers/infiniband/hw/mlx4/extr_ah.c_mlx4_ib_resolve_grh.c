#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx4_ib_dev {int dummy; } ;
struct in6_addr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw; } ;
struct TYPE_4__ {TYPE_1__ dgid; } ;
struct ib_ah_attr {TYPE_2__ grh; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct in6_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_get_ll_mac (struct in6_addr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdma_get_mcast_mac (struct in6_addr*,int /*<<< orphan*/ *) ; 
 scalar_t__ rdma_is_multicast_addr (struct in6_addr*) ; 
 scalar_t__ rdma_link_local_addr (struct in6_addr*) ; 

int mlx4_ib_resolve_grh(struct mlx4_ib_dev *dev, const struct ib_ah_attr *ah_attr,
			u8 *mac, int *is_mcast, u8 port)
{
	struct in6_addr in6;

	*is_mcast = 0;

	memcpy(&in6, ah_attr->grh.dgid.raw, sizeof in6);
	if (rdma_link_local_addr(&in6))
		rdma_get_ll_mac(&in6, mac);
	else if (rdma_is_multicast_addr(&in6)) {
		rdma_get_mcast_mac(&in6, mac);
		*is_mcast = 1;
	} else
		return -EINVAL;

	return 0;
}