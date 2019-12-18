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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int len; int os_skbs; int index; struct sk_buff** arr; } ;
struct ehea_port_res {int /*<<< orphan*/  qp; TYPE_2__ rq1_skba; TYPE_1__* port; } ;
struct TYPE_3__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_L_PKT_SIZE ; 
 int /*<<< orphan*/  __EHEA_STOP_XFER ; 
 int /*<<< orphan*/  ehea_driver_flags ; 
 int /*<<< orphan*/  ehea_info (char*) ; 
 int /*<<< orphan*/  ehea_update_rq1a (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehea_refill_rq1(struct ehea_port_res *pr, int index, int nr_of_wqes)
{
	struct sk_buff **skb_arr_rq1 = pr->rq1_skba.arr;
	struct net_device *dev = pr->port->netdev;
	int max_index_mask = pr->rq1_skba.len - 1;
	int fill_wqes = pr->rq1_skba.os_skbs + nr_of_wqes;
	int adder = 0;
	int i;

	pr->rq1_skba.os_skbs = 0;

	if (unlikely(test_bit(__EHEA_STOP_XFER, &ehea_driver_flags))) {
		if (nr_of_wqes > 0)
			pr->rq1_skba.index = index;
		pr->rq1_skba.os_skbs = fill_wqes;
		return;
	}

	for (i = 0; i < fill_wqes; i++) {
		if (!skb_arr_rq1[index]) {
			skb_arr_rq1[index] = netdev_alloc_skb(dev,
							      EHEA_L_PKT_SIZE);
			if (!skb_arr_rq1[index]) {
				ehea_info("Unable to allocate enough skb in the array\n");
				pr->rq1_skba.os_skbs = fill_wqes - i;
				break;
			}
		}
		index--;
		index &= max_index_mask;
		adder++;
	}

	if (adder == 0)
		return;

	/* Ring doorbell */
	ehea_update_rq1a(pr->qp, adder);
}