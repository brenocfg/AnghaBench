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
struct mlx4_ib_ah {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct ib_ah_attr {int ah_flags; int /*<<< orphan*/  port_num; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ib_ah* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int IB_AH_GRH ; 
 scalar_t__ IB_LINK_LAYER_ETHERNET ; 
 scalar_t__ IS_ERR (struct ib_ah*) ; 
 struct ib_ah* create_ib_ah (struct ib_pd*,struct ib_ah_attr*,struct mlx4_ib_ah*) ; 
 struct ib_ah* create_iboe_ah (struct ib_pd*,struct ib_ah_attr*,struct mlx4_ib_ah*) ; 
 int /*<<< orphan*/  kfree (struct mlx4_ib_ah*) ; 
 struct mlx4_ib_ah* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_port_get_link_layer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct ib_ah *mlx4_ib_create_ah(struct ib_pd *pd, struct ib_ah_attr *ah_attr)
{
	struct mlx4_ib_ah *ah;
	struct ib_ah *ret;

	ah = kzalloc(sizeof *ah, GFP_ATOMIC);
	if (!ah)
		return ERR_PTR(-ENOMEM);

	if (rdma_port_get_link_layer(pd->device, ah_attr->port_num) == IB_LINK_LAYER_ETHERNET) {
		if (!(ah_attr->ah_flags & IB_AH_GRH)) {
			ret = ERR_PTR(-EINVAL);
		} else {
			/*
			 * TBD: need to handle the case when we get
			 * called in an atomic context and there we
			 * might sleep.  We don't expect this
			 * currently since we're working with link
			 * local addresses which we can translate
			 * without going to sleep.
			 */
			ret = create_iboe_ah(pd, ah_attr, ah);
		}

		if (IS_ERR(ret))
			kfree(ah);

		return ret;
	} else
		return create_ib_ah(pd, ah_attr, ah); /* never fails */
}