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
struct ib_wc {int dummy; } ;
struct ib_mad {int dummy; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_LINK_LAYER_ETHERNET 129 
#define  IB_LINK_LAYER_INFINIBAND 128 
 int ib_process_mad (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_wc*,struct ib_grh*,struct ib_mad*,struct ib_mad*) ; 
 int iboe_process_mad (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_wc*,struct ib_grh*,struct ib_mad*,struct ib_mad*) ; 
 int rdma_port_get_link_layer (struct ib_device*,int /*<<< orphan*/ ) ; 

int mlx4_ib_process_mad(struct ib_device *ibdev, int mad_flags, u8 port_num,
			struct ib_wc *in_wc, struct ib_grh *in_grh,
			struct ib_mad *in_mad, struct ib_mad *out_mad)
{
	switch (rdma_port_get_link_layer(ibdev, port_num)) {
	case IB_LINK_LAYER_INFINIBAND:
		return ib_process_mad(ibdev, mad_flags, port_num, in_wc,
				      in_grh, in_mad, out_mad);
	case IB_LINK_LAYER_ETHERNET:
		return iboe_process_mad(ibdev, mad_flags, port_num, in_wc,
					  in_grh, in_mad, out_mad);
	default:
		return -EINVAL;
	}
}