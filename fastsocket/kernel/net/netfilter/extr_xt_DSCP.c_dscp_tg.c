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
typedef  int u_int8_t ;
struct xt_target_param {struct xt_DSCP_info* targinfo; } ;
struct xt_DSCP_info {int dscp; } ;
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 unsigned int XT_CONTINUE ; 
 scalar_t__ XT_DSCP_MASK ; 
 int XT_DSCP_SHIFT ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ipv4_change_dsfield (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ipv4_get_dsfield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int) ; 

__attribute__((used)) static unsigned int
dscp_tg(struct sk_buff *skb, const struct xt_target_param *par)
{
	const struct xt_DSCP_info *dinfo = par->targinfo;
	u_int8_t dscp = ipv4_get_dsfield(ip_hdr(skb)) >> XT_DSCP_SHIFT;

	if (dscp != dinfo->dscp) {
		if (!skb_make_writable(skb, sizeof(struct iphdr)))
			return NF_DROP;

		ipv4_change_dsfield(ip_hdr(skb), (__u8)(~XT_DSCP_MASK),
				    dinfo->dscp << XT_DSCP_SHIFT);

	}
	return XT_CONTINUE;
}