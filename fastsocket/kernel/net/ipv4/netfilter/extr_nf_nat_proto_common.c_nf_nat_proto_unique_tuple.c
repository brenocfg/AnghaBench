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
typedef  unsigned int u_int16_t ;
struct TYPE_10__ {int /*<<< orphan*/  all; } ;
struct TYPE_9__ {int /*<<< orphan*/  all; } ;
struct nf_nat_range {int flags; TYPE_2__ max; TYPE_1__ min; } ;
struct TYPE_15__ {int /*<<< orphan*/  all; } ;
struct TYPE_11__ {int /*<<< orphan*/  ip; } ;
struct TYPE_16__ {TYPE_7__ u; TYPE_3__ u3; } ;
struct TYPE_13__ {int /*<<< orphan*/  all; } ;
struct TYPE_12__ {int /*<<< orphan*/  ip; } ;
struct TYPE_14__ {TYPE_5__ u; TYPE_4__ u3; } ;
struct nf_conntrack_tuple {TYPE_8__ src; TYPE_6__ dst; } ;
struct nf_conn {int dummy; } ;
typedef  enum nf_nat_manip_type { ____Placeholder_nf_nat_manip_type } nf_nat_manip_type ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int IP_NAT_MANIP_DST ; 
 int IP_NAT_MANIP_SRC ; 
 int IP_NAT_RANGE_PROTO_RANDOM ; 
 int IP_NAT_RANGE_PROTO_SPECIFIED ; 
 int /*<<< orphan*/  htons (unsigned int) ; 
 scalar_t__ nf_nat_used_tuple (struct nf_conntrack_tuple*,struct nf_conn const*) ; 
 unsigned int ntohs (int /*<<< orphan*/ ) ; 
 unsigned int secure_ipv4_port_ephemeral (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool nf_nat_proto_unique_tuple(struct nf_conntrack_tuple *tuple,
			       const struct nf_nat_range *range,
			       enum nf_nat_manip_type maniptype,
			       const struct nf_conn *ct,
			       u_int16_t *rover)
{
	unsigned int range_size, min, i;
	__be16 *portptr;
	u_int16_t off;

	if (maniptype == IP_NAT_MANIP_SRC)
		portptr = &tuple->src.u.all;
	else
		portptr = &tuple->dst.u.all;

	/* If no range specified... */
	if (!(range->flags & IP_NAT_RANGE_PROTO_SPECIFIED)) {
		/* If it's dst rewrite, can't change port */
		if (maniptype == IP_NAT_MANIP_DST)
			return false;

		if (ntohs(*portptr) < 1024) {
			/* Loose convention: >> 512 is credential passing */
			if (ntohs(*portptr) < 512) {
				min = 1;
				range_size = 511 - min + 1;
			} else {
				min = 600;
				range_size = 1023 - min + 1;
			}
		} else {
			min = 1024;
			range_size = 65535 - 1024 + 1;
		}
	} else {
		min = ntohs(range->min.all);
		range_size = ntohs(range->max.all) - min + 1;
	}

	if (range->flags & IP_NAT_RANGE_PROTO_RANDOM)
		off = secure_ipv4_port_ephemeral(tuple->src.u3.ip, tuple->dst.u3.ip,
						 maniptype == IP_NAT_MANIP_SRC
						 ? tuple->dst.u.all
						 : tuple->src.u.all);
	else
		off = *rover;

	for (i = 0; i < range_size; i++, off++) {
		*portptr = htons(min + off % range_size);
		if (nf_nat_used_tuple(tuple, ct))
			continue;
		if (!(range->flags & IP_NAT_RANGE_PROTO_RANDOM))
			*rover = off;
		return true;
	}
	return false;
}