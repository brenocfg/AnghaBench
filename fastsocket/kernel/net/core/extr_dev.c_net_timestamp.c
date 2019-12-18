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
struct TYPE_2__ {scalar_t__ tv64; } ;
struct sk_buff {TYPE_1__ tstamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  __net_timestamp (struct sk_buff*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netstamp_needed ; 

__attribute__((used)) static inline void net_timestamp(struct sk_buff *skb)
{
	if (atomic_read(&netstamp_needed))
		__net_timestamp(skb);
	else
		skb->tstamp.tv64 = 0;
}