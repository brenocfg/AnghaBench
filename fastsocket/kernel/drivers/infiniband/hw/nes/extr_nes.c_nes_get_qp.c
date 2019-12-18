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
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_device {struct nes_adapter* nesadapter; } ;
struct nes_adapter {int max_qp; TYPE_1__** qp_table; } ;
struct ib_qp {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {struct ib_qp ibqp; } ;

/* Variables and functions */
 int NES_FIRST_QPN ; 
 struct nes_vnic* to_nesvnic (struct ib_device*) ; 

struct ib_qp *nes_get_qp(struct ib_device *device, int qpn)
{
	struct nes_vnic *nesvnic = to_nesvnic(device);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_adapter *nesadapter = nesdev->nesadapter;

	if ((qpn < NES_FIRST_QPN) || (qpn >= (NES_FIRST_QPN + nesadapter->max_qp)))
		return NULL;

	return &nesadapter->qp_table[qpn - NES_FIRST_QPN]->ibqp;
}