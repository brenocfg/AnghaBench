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
struct TYPE_2__ {long expires; } ;
struct nf_conn {TYPE_1__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_TIMEOUT ; 
 long HZ ; 
 int /*<<< orphan*/  NLA_PUT_BE32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (long) ; 
 long jiffies ; 

__attribute__((used)) static inline int
ctnetlink_dump_timeout(struct sk_buff *skb, const struct nf_conn *ct)
{
	long timeout = (ct->timeout.expires - jiffies) / HZ;

	if (timeout < 0)
		timeout = 0;

	NLA_PUT_BE32(skb, CTA_TIMEOUT, htonl(timeout));
	return 0;

nla_put_failure:
	return -1;
}