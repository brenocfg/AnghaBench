#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct ehea_qp {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  poll_receive_errors; } ;
struct TYPE_7__ {int len; struct sk_buff** arr; } ;
struct TYPE_6__ {int len; struct sk_buff** arr; } ;
struct TYPE_5__ {int len; struct sk_buff** arr; } ;
struct ehea_port_res {int rx_packets; int /*<<< orphan*/  rx_bytes; TYPE_4__ p_stats; int /*<<< orphan*/  napi; TYPE_3__ rq3_skba; TYPE_2__ rq2_skba; TYPE_1__ rq1_skba; struct ehea_qp* qp; struct ehea_port* port; } ;
struct ehea_port {scalar_t__ vgrp; } ;
struct ehea_cqe {int status; int /*<<< orphan*/  vlan_tag; scalar_t__ num_bytes_transfered; } ;

/* Variables and functions */
 int EHEA_CQE_VLAN_TAG_XTRACT ; 
 int /*<<< orphan*/  EHEA_L_PKT_SIZE ; 
 int /*<<< orphan*/  ehea_check_cqe (struct ehea_cqe*,int*) ; 
 int /*<<< orphan*/  ehea_dump (struct ehea_cqe*,int,char*) ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 int /*<<< orphan*/  ehea_fill_skb (struct net_device*,struct sk_buff*,struct ehea_cqe*,struct ehea_port_res*) ; 
 int /*<<< orphan*/  ehea_inc_rq1 (struct ehea_qp*) ; 
 int /*<<< orphan*/  ehea_info (char*) ; 
 struct ehea_cqe* ehea_poll_rq1 (struct ehea_qp*,int*) ; 
 int /*<<< orphan*/  ehea_refill_rq1 (struct ehea_port_res*,int,int) ; 
 int /*<<< orphan*/  ehea_refill_rq2 (struct ehea_port_res*,int) ; 
 int /*<<< orphan*/  ehea_refill_rq3 (struct ehea_port_res*,int) ; 
 int ehea_treat_poll_error (struct ehea_port_res*,int,struct ehea_cqe*,int*,int*) ; 
 struct sk_buff* get_skb_by_index (struct sk_buff**,int,struct ehea_cqe*) ; 
 struct sk_buff* get_skb_by_index_ll (struct sk_buff**,int,int) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_msg_rx_err (struct ehea_port*) ; 
 scalar_t__ netif_msg_rx_status (struct ehea_port*) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,char*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlan_gro_receive (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int ehea_proc_rwqes(struct net_device *dev,
			   struct ehea_port_res *pr,
			   int budget)
{
	struct ehea_port *port = pr->port;
	struct ehea_qp *qp = pr->qp;
	struct ehea_cqe *cqe;
	struct sk_buff *skb;
	struct sk_buff **skb_arr_rq1 = pr->rq1_skba.arr;
	struct sk_buff **skb_arr_rq2 = pr->rq2_skba.arr;
	struct sk_buff **skb_arr_rq3 = pr->rq3_skba.arr;
	int skb_arr_rq1_len = pr->rq1_skba.len;
	int skb_arr_rq2_len = pr->rq2_skba.len;
	int skb_arr_rq3_len = pr->rq3_skba.len;
	int processed, processed_rq1, processed_rq2, processed_rq3;
	u64 processed_bytes = 0;
	int wqe_index, last_wqe_index, rq, port_reset;

	processed = processed_rq1 = processed_rq2 = processed_rq3 = 0;
	last_wqe_index = 0;

	cqe = ehea_poll_rq1(qp, &wqe_index);
	while ((processed < budget) && cqe) {
		ehea_inc_rq1(qp);
		processed_rq1++;
		processed++;
		if (netif_msg_rx_status(port))
			ehea_dump(cqe, sizeof(*cqe), "CQE");

		last_wqe_index = wqe_index;
		rmb();
		if (!ehea_check_cqe(cqe, &rq)) {
			if (rq == 1) {
				/* LL RQ1 */
				skb = get_skb_by_index_ll(skb_arr_rq1,
							  skb_arr_rq1_len,
							  wqe_index);
				if (unlikely(!skb)) {
					if (netif_msg_rx_err(port))
						ehea_info("LL rq1: skb=NULL");

					skb = netdev_alloc_skb(dev,
							       EHEA_L_PKT_SIZE);
					if (!skb){
						ehea_error("Not enough memory to allocate skb\n");
						break;
					}
				}
				skb_copy_to_linear_data(skb, ((char *)cqe) + 64,
						 cqe->num_bytes_transfered - 4);
				ehea_fill_skb(dev, skb, cqe, pr);
			} else if (rq == 2) {
				/* RQ2 */
				skb = get_skb_by_index(skb_arr_rq2,
						       skb_arr_rq2_len, cqe);
				if (unlikely(!skb)) {
					if (netif_msg_rx_err(port))
						ehea_error("rq2: skb=NULL");
					break;
				}
				ehea_fill_skb(dev, skb, cqe, pr);
				processed_rq2++;
			} else {
				/* RQ3 */
				skb = get_skb_by_index(skb_arr_rq3,
						       skb_arr_rq3_len, cqe);
				if (unlikely(!skb)) {
					if (netif_msg_rx_err(port))
						ehea_error("rq3: skb=NULL");
					break;
				}
				ehea_fill_skb(dev, skb, cqe, pr);
				processed_rq3++;
			}

			processed_bytes += skb->len;

			if ((cqe->status & EHEA_CQE_VLAN_TAG_XTRACT)
			    && port->vgrp) {
				vlan_gro_receive(&pr->napi, port->vgrp,
						cqe->vlan_tag, skb);
			} else {
				napi_gro_receive(&pr->napi, skb);
			}
		} else {
			pr->p_stats.poll_receive_errors++;
			port_reset = ehea_treat_poll_error(pr, rq, cqe,
							   &processed_rq2,
							   &processed_rq3);
			if (port_reset)
				break;
		}
		cqe = ehea_poll_rq1(qp, &wqe_index);
	}

	pr->rx_packets += processed;
	pr->rx_bytes += processed_bytes;

	ehea_refill_rq1(pr, last_wqe_index, processed_rq1);
	ehea_refill_rq2(pr, processed_rq2);
	ehea_refill_rq3(pr, processed_rq3);

	return processed;
}