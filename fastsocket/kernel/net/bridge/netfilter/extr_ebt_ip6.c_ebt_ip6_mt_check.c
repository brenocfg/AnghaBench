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
struct xt_mtchk_param {struct ebt_ip6_info* matchinfo; struct ebt_entry* entryinfo; } ;
struct ebt_ip6_info {int bitmask; int invflags; scalar_t__ protocol; scalar_t__* dport; scalar_t__* sport; } ;
struct ebt_entry {scalar_t__ ethproto; int invflags; } ;

/* Variables and functions */
 int EBT_IP6_DPORT ; 
 int EBT_IP6_MASK ; 
 int EBT_IP6_PROTO ; 
 int EBT_IP6_SPORT ; 
 int EBT_IPROTO ; 
 int /*<<< orphan*/  ETH_P_IPV6 ; 
 scalar_t__ IPPROTO_DCCP ; 
 scalar_t__ IPPROTO_SCTP ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ IPPROTO_UDPLITE ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ebt_ip6_mt_check(const struct xt_mtchk_param *par)
{
	const struct ebt_entry *e = par->entryinfo;
	struct ebt_ip6_info *info = par->matchinfo;

	if (e->ethproto != htons(ETH_P_IPV6) || e->invflags & EBT_IPROTO)
		return false;
	if (info->bitmask & ~EBT_IP6_MASK || info->invflags & ~EBT_IP6_MASK)
		return false;
	if (info->bitmask & (EBT_IP6_DPORT | EBT_IP6_SPORT)) {
		if (info->invflags & EBT_IP6_PROTO)
			return false;
		if (info->protocol != IPPROTO_TCP &&
		    info->protocol != IPPROTO_UDP &&
		    info->protocol != IPPROTO_UDPLITE &&
		    info->protocol != IPPROTO_SCTP &&
		    info->protocol != IPPROTO_DCCP)
			return false;
	}
	if (info->bitmask & EBT_IP6_DPORT && info->dport[0] > info->dport[1])
		return false;
	if (info->bitmask & EBT_IP6_SPORT && info->sport[0] > info->sport[1])
		return false;
	return true;
}