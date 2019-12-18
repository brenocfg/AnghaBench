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
struct net {int dummy; } ;
struct ip6_flowlabel {scalar_t__ label; struct net* fl_net; struct ip6_flowlabel* next; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 size_t FL_HASH (scalar_t__) ; 
 struct ip6_flowlabel** fl_ht ; 

__attribute__((used)) static inline struct ip6_flowlabel *__fl_lookup(struct net *net, __be32 label)
{
	struct ip6_flowlabel *fl;

	for (fl=fl_ht[FL_HASH(label)]; fl; fl = fl->next) {
		if (fl->label == label && fl->fl_net == net)
			return fl;
	}
	return NULL;
}