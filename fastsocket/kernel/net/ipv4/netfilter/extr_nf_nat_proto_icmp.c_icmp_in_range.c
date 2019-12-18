#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  id; } ;
union nf_conntrack_man_proto {TYPE_4__ icmp; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {TYPE_1__ icmp; } ;
struct TYPE_7__ {TYPE_2__ u; } ;
struct nf_conntrack_tuple {TYPE_3__ src; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;

/* Variables and functions */
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
icmp_in_range(const struct nf_conntrack_tuple *tuple,
	      enum nf_nat_manip_type maniptype,
	      const union nf_conntrack_man_proto *min,
	      const union nf_conntrack_man_proto *max)
{
	return ntohs(tuple->src.u.icmp.id) >= ntohs(min->icmp.id) &&
	       ntohs(tuple->src.u.icmp.id) <= ntohs(max->icmp.id);
}