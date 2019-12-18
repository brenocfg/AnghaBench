#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ all; } ;
struct TYPE_6__ {scalar_t__ ip; } ;
struct TYPE_8__ {TYPE_2__ u; TYPE_1__ u3; } ;
struct TYPE_10__ {scalar_t__ protonum; } ;
struct nf_conntrack_tuple {TYPE_3__ src; TYPE_5__ dst; } ;
struct nf_conn {TYPE_4__* tuplehash; } ;
struct TYPE_9__ {struct nf_conntrack_tuple tuple; } ;

/* Variables and functions */
 size_t IP_CT_DIR_ORIGINAL ; 

__attribute__((used)) static inline int
same_src(const struct nf_conn *ct,
	 const struct nf_conntrack_tuple *tuple)
{
	const struct nf_conntrack_tuple *t;

	t = &ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple;
	return (t->dst.protonum == tuple->dst.protonum &&
		t->src.u3.ip == tuple->src.u3.ip &&
		t->src.u.all == tuple->src.u.all);
}