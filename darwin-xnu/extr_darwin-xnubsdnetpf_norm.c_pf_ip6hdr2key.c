#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  v6addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  v6addr; } ;
struct pf_fragment {TYPE_2__ fr_dstx; TYPE_1__ fr_srcx; int /*<<< orphan*/  fr_af; int /*<<< orphan*/  fr_id6; int /*<<< orphan*/  fr_p; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct ip6_frag {int /*<<< orphan*/  ip6f_ident; int /*<<< orphan*/  ip6f_nxt; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 

__attribute__((used)) static void
pf_ip6hdr2key(struct pf_fragment *key, struct ip6_hdr *ip6,
    struct ip6_frag *fh)
{
	key->fr_p = fh->ip6f_nxt;
	key->fr_id6 = fh->ip6f_ident;
	key->fr_af = AF_INET6;
	key->fr_srcx.v6addr = ip6->ip6_src;
	key->fr_dstx.v6addr = ip6->ip6_dst;
}