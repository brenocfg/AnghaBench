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
typedef  enum ip_conntrack_info { ____Placeholder_ip_conntrack_info } ip_conntrack_info ;

/* Variables and functions */
 int nf_conntrack_broadcast_help (struct sk_buff*,unsigned int,struct nf_conn*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int netbios_ns_help(struct sk_buff *skb, unsigned int protoff,
                  struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	return nf_conntrack_broadcast_help(skb, protoff, ct, ctinfo, timeout);
}