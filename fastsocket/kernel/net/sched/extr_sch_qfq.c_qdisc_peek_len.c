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
struct sk_buff {int dummy; } ;
struct Qdisc {TYPE_1__* ops; } ;
struct TYPE_2__ {struct sk_buff* (* peek ) (struct Qdisc*) ;} ;

/* Variables and functions */
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 struct sk_buff* stub1 (struct Qdisc*) ; 

__attribute__((used)) static unsigned int qdisc_peek_len(struct Qdisc *sch)
{
	struct sk_buff *skb;

	skb = sch->ops->peek(sch);
	return skb ? qdisc_pkt_len(skb) : 0;
}