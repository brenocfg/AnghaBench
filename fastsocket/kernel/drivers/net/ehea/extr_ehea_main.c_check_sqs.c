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
struct ehea_swqe {int immediate_data_length; int /*<<< orphan*/  tx_control; int /*<<< orphan*/  wr_id; } ;
struct ehea_port_res {scalar_t__ sq_restart_flag; int /*<<< orphan*/  port; int /*<<< orphan*/  qp; int /*<<< orphan*/  swqe_avail; } ;
struct ehea_port {int num_def_qps; int /*<<< orphan*/  restart_wq; struct ehea_port_res* port_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_SWQE_IMM_DATA_PRESENT ; 
 int /*<<< orphan*/  EHEA_SWQE_PURGE ; 
 int /*<<< orphan*/  EHEA_SWQE_SIGNALLED_COMPLETION ; 
 int /*<<< orphan*/  SWQE_HEADER_SIZE ; 
 int /*<<< orphan*/  SWQE_RESTART_CHECK ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 struct ehea_swqe* ehea_get_swqe (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ehea_post_swqe (int /*<<< orphan*/ ,struct ehea_swqe*) ; 
 int /*<<< orphan*/  ehea_schedule_port_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ehea_swqe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_sqs(struct ehea_port *port)
{
	struct ehea_swqe *swqe;
	int swqe_index;
	int i, k;

	for (i = 0; i < port->num_def_qps; i++) {
		struct ehea_port_res *pr = &port->port_res[i];
		int ret;
		k = 0;
		swqe = ehea_get_swqe(pr->qp, &swqe_index);
		memset(swqe, 0, SWQE_HEADER_SIZE);
		atomic_dec(&pr->swqe_avail);

		swqe->tx_control |= EHEA_SWQE_PURGE;
		swqe->wr_id = SWQE_RESTART_CHECK;
		swqe->tx_control |= EHEA_SWQE_SIGNALLED_COMPLETION;
		swqe->tx_control |= EHEA_SWQE_IMM_DATA_PRESENT;
		swqe->immediate_data_length = 80;

		ehea_post_swqe(pr->qp, swqe);

		ret = wait_event_timeout(port->restart_wq,
					 pr->sq_restart_flag == 0,
					 msecs_to_jiffies(100));

		if (!ret) {
			ehea_error("HW/SW queues out of sync");
			ehea_schedule_port_reset(pr->port);
			return;
		}
	}
}