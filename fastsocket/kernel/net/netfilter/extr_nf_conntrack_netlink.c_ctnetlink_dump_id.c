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
struct sk_buff {int dummy; } ;
struct nf_conn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTA_ID ; 
 int /*<<< orphan*/  NLA_PUT_BE32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htonl (unsigned long) ; 

__attribute__((used)) static inline int
ctnetlink_dump_id(struct sk_buff *skb, const struct nf_conn *ct)
{
	NLA_PUT_BE32(skb, CTA_ID, htonl((unsigned long)ct));
	return 0;

nla_put_failure:
	return -1;
}