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
struct TYPE_2__ {int /*<<< orphan*/  tv64; } ;
struct sk_buff {int /*<<< orphan*/  dev; TYPE_1__ tstamp; } ;
struct rps_dev_flow {int /*<<< orphan*/  last_qtail; } ;

/* Variables and functions */
 int NET_RX_DROP ; 
 int enqueue_to_backlog (struct sk_buff*,int,int /*<<< orphan*/ *) ; 
 int get_rps_cpu (int /*<<< orphan*/ ,struct sk_buff*,struct rps_dev_flow**) ; 
 int /*<<< orphan*/  net_timestamp (struct sk_buff*) ; 
 scalar_t__ netpoll_rx (struct sk_buff*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  trace_netif_rx (struct sk_buff*) ; 

int netif_rx(struct sk_buff *skb)
{
	struct rps_dev_flow voidflow, *rflow = &voidflow;
	int cpu;

	/* if netpoll wants it, pretend we never saw it */
	if (netpoll_rx(skb))
		return NET_RX_DROP;

	if (!skb->tstamp.tv64)
		net_timestamp(skb);

	trace_netif_rx(skb);
	cpu = get_rps_cpu(skb->dev, skb, &rflow);
	if (cpu < 0)
		cpu = smp_processor_id();

	return enqueue_to_backlog(skb, cpu, &rflow->last_qtail);
}