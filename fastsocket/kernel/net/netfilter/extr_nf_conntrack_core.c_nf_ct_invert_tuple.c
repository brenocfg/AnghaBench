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
struct TYPE_3__ {int dir; int /*<<< orphan*/  protonum; } ;
struct TYPE_4__ {int /*<<< orphan*/  l3num; } ;
struct nf_conntrack_tuple {TYPE_1__ dst; TYPE_2__ src; } ;
struct nf_conntrack_l4proto {int (* invert_tuple ) (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*) ;} ;
struct nf_conntrack_l3proto {scalar_t__ (* invert_tuple ) (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct nf_conntrack_tuple*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*) ; 
 int stub2 (struct nf_conntrack_tuple*,struct nf_conntrack_tuple const*) ; 

bool
nf_ct_invert_tuple(struct nf_conntrack_tuple *inverse,
		   const struct nf_conntrack_tuple *orig,
		   const struct nf_conntrack_l3proto *l3proto,
		   const struct nf_conntrack_l4proto *l4proto)
{
	memset(inverse, 0, sizeof(*inverse));

	inverse->src.l3num = orig->src.l3num;
	if (l3proto->invert_tuple(inverse, orig) == 0)
		return false;

	inverse->dst.dir = !orig->dst.dir;

	inverse->dst.protonum = orig->dst.protonum;
	return l4proto->invert_tuple(inverse, orig);
}