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
struct xt_match_param {scalar_t__ fragoff; int* hotdrop; int /*<<< orphan*/  thoff; struct xt_dccp_info* matchinfo; } ;
struct xt_dccp_info {scalar_t__* spts; scalar_t__* dpts; int /*<<< orphan*/  invflags; int /*<<< orphan*/  flags; int /*<<< orphan*/  option; int /*<<< orphan*/  typemask; } ;
struct sk_buff {int dummy; } ;
struct dccp_hdr {int /*<<< orphan*/  dccph_dport; int /*<<< orphan*/  dccph_sport; } ;
typedef  int /*<<< orphan*/  _dh ;

/* Variables and functions */
 scalar_t__ DCCHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XT_DCCP_DEST_PORTS ; 
 int /*<<< orphan*/  XT_DCCP_OPTION ; 
 int /*<<< orphan*/  XT_DCCP_SRC_PORTS ; 
 int /*<<< orphan*/  XT_DCCP_TYPE ; 
 int match_option (int /*<<< orphan*/ ,struct sk_buff const*,int /*<<< orphan*/ ,struct dccp_hdr const*,int*) ; 
 int match_types (struct dccp_hdr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct dccp_hdr* skb_header_pointer (struct sk_buff const*,int /*<<< orphan*/ ,int,struct dccp_hdr*) ; 

__attribute__((used)) static bool
dccp_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_dccp_info *info = par->matchinfo;
	const struct dccp_hdr *dh;
	struct dccp_hdr _dh;

	if (par->fragoff != 0)
		return false;

	dh = skb_header_pointer(skb, par->thoff, sizeof(_dh), &_dh);
	if (dh == NULL) {
		*par->hotdrop = true;
		return false;
	}

	return  DCCHECK(ntohs(dh->dccph_sport) >= info->spts[0]
			&& ntohs(dh->dccph_sport) <= info->spts[1],
			XT_DCCP_SRC_PORTS, info->flags, info->invflags)
		&& DCCHECK(ntohs(dh->dccph_dport) >= info->dpts[0]
			&& ntohs(dh->dccph_dport) <= info->dpts[1],
			XT_DCCP_DEST_PORTS, info->flags, info->invflags)
		&& DCCHECK(match_types(dh, info->typemask),
			   XT_DCCP_TYPE, info->flags, info->invflags)
		&& DCCHECK(match_option(info->option, skb, par->thoff, dh,
					par->hotdrop),
			   XT_DCCP_OPTION, info->flags, info->invflags);
}