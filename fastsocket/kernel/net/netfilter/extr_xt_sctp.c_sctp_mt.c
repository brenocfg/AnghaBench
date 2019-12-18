#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_sctp_info {scalar_t__* spts; scalar_t__* dpts; int /*<<< orphan*/  invflags; int /*<<< orphan*/  flags; } ;
struct xt_match_param {scalar_t__ fragoff; int* hotdrop; scalar_t__ thoff; struct xt_sctp_info* matchinfo; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dest; int /*<<< orphan*/  source; } ;
typedef  TYPE_1__ sctp_sctphdr_t ;
typedef  int /*<<< orphan*/  _sh ;

/* Variables and functions */
 scalar_t__ SCCHECK (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XT_SCTP_CHUNK_TYPES ; 
 int /*<<< orphan*/  XT_SCTP_DEST_PORTS ; 
 int /*<<< orphan*/  XT_SCTP_SRC_PORTS ; 
 int /*<<< orphan*/  duprintf (char*,...) ; 
 int match_packet (struct sk_buff const*,scalar_t__,struct xt_sctp_info const*,int*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 TYPE_1__* skb_header_pointer (struct sk_buff const*,scalar_t__,int,TYPE_1__*) ; 

__attribute__((used)) static bool
sctp_mt(const struct sk_buff *skb, const struct xt_match_param *par)
{
	const struct xt_sctp_info *info = par->matchinfo;
	const sctp_sctphdr_t *sh;
	sctp_sctphdr_t _sh;

	if (par->fragoff != 0) {
		duprintf("Dropping non-first fragment.. FIXME\n");
		return false;
	}

	sh = skb_header_pointer(skb, par->thoff, sizeof(_sh), &_sh);
	if (sh == NULL) {
		duprintf("Dropping evil TCP offset=0 tinygram.\n");
		*par->hotdrop = true;
		return false;
	}
	duprintf("spt: %d\tdpt: %d\n", ntohs(sh->source), ntohs(sh->dest));

	return  SCCHECK(ntohs(sh->source) >= info->spts[0]
			&& ntohs(sh->source) <= info->spts[1],
			XT_SCTP_SRC_PORTS, info->flags, info->invflags)
		&& SCCHECK(ntohs(sh->dest) >= info->dpts[0]
			&& ntohs(sh->dest) <= info->dpts[1],
			XT_SCTP_DEST_PORTS, info->flags, info->invflags)
		&& SCCHECK(match_packet(skb, par->thoff + sizeof(sctp_sctphdr_t),
					info, par->hotdrop),
			   XT_SCTP_CHUNK_TYPES, info->flags, info->invflags);
}