#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ qpn; } ;
struct mlx4_ib_qp {TYPE_2__ mqp; } ;
struct mlx4_ib_dev {TYPE_4__* dev; } ;
struct TYPE_8__ {int num_ports; scalar_t__* qp0_proxy; } ;
struct TYPE_6__ {scalar_t__ base_sqpn; } ;
struct TYPE_9__ {TYPE_3__ caps; TYPE_1__ phys_caps; } ;

/* Variables and functions */
 scalar_t__ mlx4_is_master (TYPE_4__*) ; 
 scalar_t__ mlx4_is_mfunc (TYPE_4__*) ; 

__attribute__((used)) static int is_qp0(struct mlx4_ib_dev *dev, struct mlx4_ib_qp *qp)
{
	int proxy_qp0 = 0;
	int real_qp0 = 0;
	int i;
	/* PPF or Native -- real QP0 */
	real_qp0 = ((mlx4_is_master(dev->dev) || !mlx4_is_mfunc(dev->dev)) &&
		    qp->mqp.qpn >= dev->dev->phys_caps.base_sqpn &&
		    qp->mqp.qpn <= dev->dev->phys_caps.base_sqpn + 1);
	if (real_qp0)
		return 1;
	/* VF or PF -- proxy QP0 */
	if (mlx4_is_mfunc(dev->dev)) {
		for (i = 0; i < dev->dev->caps.num_ports; i++) {
			if (qp->mqp.qpn == dev->dev->caps.qp0_proxy[i]) {
				proxy_qp0 = 1;
				break;
			}
		}
	}
	return proxy_qp0;
}