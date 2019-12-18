#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct nf_nat_range {TYPE_2__ member_4; TYPE_1__ member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct nf_conn {TYPE_8__* tuplehash; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_13__ {int /*<<< orphan*/  ip; } ;
struct TYPE_14__ {TYPE_5__ u3; } ;
struct TYPE_11__ {int /*<<< orphan*/  ip; } ;
struct TYPE_12__ {TYPE_3__ u3; } ;
struct TYPE_15__ {TYPE_6__ src; TYPE_4__ dst; } ;
struct TYPE_16__ {TYPE_7__ tuple; } ;

/* Variables and functions */
 scalar_t__ HOOK2MANIP (unsigned int) ; 
 size_t IP_CT_DIR_REPLY ; 
 scalar_t__ IP_NAT_MANIP_SRC ; 
 int /*<<< orphan*/  IP_NAT_RANGE_MAP_IPS ; 
 unsigned int nf_nat_setup_info (struct nf_conn*,struct nf_nat_range*,scalar_t__) ; 
 int /*<<< orphan*/  pr_debug (char*,struct nf_conn*,int /*<<< orphan*/ *) ; 

unsigned int
alloc_null_binding(struct nf_conn *ct, unsigned int hooknum)
{
	/* Force range to this IP; let proto decide mapping for
	   per-proto parts (hence not IP_NAT_RANGE_PROTO_SPECIFIED).
	   Use reply in case it's already been mangled (eg local packet).
	*/
	__be32 ip
		= (HOOK2MANIP(hooknum) == IP_NAT_MANIP_SRC
		   ? ct->tuplehash[IP_CT_DIR_REPLY].tuple.dst.u3.ip
		   : ct->tuplehash[IP_CT_DIR_REPLY].tuple.src.u3.ip);
	struct nf_nat_range range
		= { IP_NAT_RANGE_MAP_IPS, ip, ip, { 0 }, { 0 } };

	pr_debug("Allocating NULL binding for %p (%pI4)\n", ct, &ip);
	return nf_nat_setup_info(ct, &range, HOOK2MANIP(hooknum));
}