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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ht; } ;

/* Variables and functions */
 int MAX_INET_PROTOS ; 
 int /*<<< orphan*/  ipv6_raw_deliver (struct sk_buff*,int) ; 
 TYPE_1__ raw_v6_hashinfo ; 
 struct sock* sk_head (int /*<<< orphan*/ *) ; 

int raw6_local_deliver(struct sk_buff *skb, int nexthdr)
{
	struct sock *raw_sk;

	raw_sk = sk_head(&raw_v6_hashinfo.ht[nexthdr & (MAX_INET_PROTOS - 1)]);
	if (raw_sk && !ipv6_raw_deliver(skb, nexthdr))
		raw_sk = NULL;

	return raw_sk != NULL;
}