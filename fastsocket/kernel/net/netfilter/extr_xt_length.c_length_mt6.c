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
typedef  scalar_t__ u_int16_t ;
struct xt_match_param {struct xt_length_info* matchinfo; } ;
struct xt_length_info {scalar_t__ const min; scalar_t__ const max; int invert; } ;
struct sk_buff {int dummy; } ;
struct ipv6hdr {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  payload_len; } ;

/* Variables and functions */
 TYPE_1__* ipv6_hdr (struct sk_buff const*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
length_mt6(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_length_info *info = par->matchinfo;
	const u_int16_t pktlen = ntohs(ipv6_hdr(skb)->payload_len) +
				 sizeof(struct ipv6hdr);

	return (pktlen >= info->min && pktlen <= info->max) ^ info->invert;
}