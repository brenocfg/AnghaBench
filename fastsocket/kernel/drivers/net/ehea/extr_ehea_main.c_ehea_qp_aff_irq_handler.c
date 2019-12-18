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
typedef  scalar_t__ u64 ;
typedef  size_t u32 ;
struct ehea_qp {int /*<<< orphan*/  fw_handle; } ;
struct ehea_port {int /*<<< orphan*/  qp_eq; int /*<<< orphan*/  adapter; TYPE_1__* port_res; } ;
struct ehea_eqe {int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {struct ehea_qp* qp; } ;

/* Variables and functions */
 scalar_t__ EHEA_AERR_RESET_MASK ; 
 scalar_t__ EHEA_AER_RESET_MASK ; 
 scalar_t__ EHEA_AER_RESTYPE_QP ; 
 size_t EHEA_BMASK_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EHEA_EQE_QP_TOKEN ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ehea_error (char*,...) ; 
 scalar_t__ ehea_error_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 struct ehea_eqe* ehea_poll_eq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_schedule_port_reset (struct ehea_port*) ; 

__attribute__((used)) static irqreturn_t ehea_qp_aff_irq_handler(int irq, void *param)
{
	struct ehea_port *port = param;
	struct ehea_eqe *eqe;
	struct ehea_qp *qp;
	u32 qp_token;
	u64 resource_type, aer, aerr;
	int reset_port = 0;

	eqe = ehea_poll_eq(port->qp_eq);

	while (eqe) {
		qp_token = EHEA_BMASK_GET(EHEA_EQE_QP_TOKEN, eqe->entry);
		ehea_error("QP aff_err: entry=0x%llx, token=0x%x",
			   eqe->entry, qp_token);

		qp = port->port_res[qp_token].qp;

		resource_type = ehea_error_data(port->adapter, qp->fw_handle,
						&aer, &aerr);

		if (resource_type == EHEA_AER_RESTYPE_QP) {
			if ((aer & EHEA_AER_RESET_MASK) ||
			    (aerr & EHEA_AERR_RESET_MASK))
				 reset_port = 1;
		} else
			reset_port = 1;   /* Reset in case of CQ or EQ error */

		eqe = ehea_poll_eq(port->qp_eq);
	}

	if (reset_port) {
		ehea_error("Resetting port");
		ehea_schedule_port_reset(port);
	}

	return IRQ_HANDLED;
}