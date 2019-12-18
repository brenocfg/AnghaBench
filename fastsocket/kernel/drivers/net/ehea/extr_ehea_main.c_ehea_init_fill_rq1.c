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
struct TYPE_4__ {int len; struct sk_buff** arr; } ;
struct ehea_port_res {int /*<<< orphan*/  qp; TYPE_2__ rq1_skba; TYPE_1__* port; } ;
struct TYPE_3__ {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_L_PKT_SIZE ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 int /*<<< orphan*/  ehea_info (char*) ; 
 int /*<<< orphan*/  ehea_update_rq1a (int /*<<< orphan*/ ,int) ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehea_init_fill_rq1(struct ehea_port_res *pr, int nr_rq1a)
{
	struct sk_buff **skb_arr_rq1 = pr->rq1_skba.arr;
	struct net_device *dev = pr->port->netdev;
	int i;

	if (nr_rq1a > pr->rq1_skba.len){
		ehea_error("NR_RQ1A bigger than skb array len\n");
		return;
	}

	for (i = 0; i < nr_rq1a; i++) {
		skb_arr_rq1[i] = netdev_alloc_skb(dev, EHEA_L_PKT_SIZE);
		if (!skb_arr_rq1[i]){
			ehea_info("No enough memory to allocate skb array\n");
			break;
		}
	}
	/* Ring doorbell */
	ehea_update_rq1a(pr->qp, i - 1);
}