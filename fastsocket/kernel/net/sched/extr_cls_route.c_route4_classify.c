#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct tcf_result {size_t classid; scalar_t__ class; } ;
struct tcf_proto {TYPE_3__* q; scalar_t__ root; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int iif; } ;
struct rtable {TYPE_1__ fl; } ;
struct route4_head {struct route4_bucket** table; TYPE_2__* fastmap; } ;
struct route4_filter {size_t id; int iif; struct route4_filter* next; struct tcf_result res; } ;
struct route4_bucket {struct route4_filter** ht; } ;
struct dst_entry {size_t tclassid; } ;
struct TYPE_6__ {size_t handle; } ;
struct TYPE_5__ {size_t id; int iif; struct route4_filter* filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUTE4_APPLY_RESULT () ; 
 struct route4_filter* ROUTE4_FAILURE ; 
 scalar_t__ TC_H_MAJ (size_t) ; 
 size_t route4_fastmap_hash (size_t,int) ; 
 size_t route4_hash_from (size_t) ; 
 size_t route4_hash_iif (int) ; 
 size_t route4_hash_to (size_t) ; 
 size_t route4_hash_wild () ; 
 int /*<<< orphan*/  route4_set_fastmap (struct route4_head*,size_t,int,struct route4_filter*) ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 

__attribute__((used)) static int route4_classify(struct sk_buff *skb, struct tcf_proto *tp,
			   struct tcf_result *res)
{
	struct route4_head *head = (struct route4_head*)tp->root;
	struct dst_entry *dst;
	struct route4_bucket *b;
	struct route4_filter *f;
	u32 id, h;
	int iif, dont_cache = 0;

	if ((dst = skb_dst(skb)) == NULL)
		goto failure;

	id = dst->tclassid;
	if (head == NULL)
		goto old_method;

	iif = ((struct rtable*)dst)->fl.iif;

	h = route4_fastmap_hash(id, iif);
	if (id == head->fastmap[h].id &&
	    iif == head->fastmap[h].iif &&
	    (f = head->fastmap[h].filter) != NULL) {
		if (f == ROUTE4_FAILURE)
			goto failure;

		*res = f->res;
		return 0;
	}

	h = route4_hash_to(id);

restart:
	if ((b = head->table[h]) != NULL) {
		for (f = b->ht[route4_hash_from(id)]; f; f = f->next)
			if (f->id == id)
				ROUTE4_APPLY_RESULT();

		for (f = b->ht[route4_hash_iif(iif)]; f; f = f->next)
			if (f->iif == iif)
				ROUTE4_APPLY_RESULT();

		for (f = b->ht[route4_hash_wild()]; f; f = f->next)
			ROUTE4_APPLY_RESULT();

	}
	if (h < 256) {
		h = 256;
		id &= ~0xFFFF;
		goto restart;
	}

	if (!dont_cache)
		route4_set_fastmap(head, id, iif, ROUTE4_FAILURE);
failure:
	return -1;

old_method:
	if (id && (TC_H_MAJ(id) == 0 ||
		   !(TC_H_MAJ(id^tp->q->handle)))) {
		res->classid = id;
		res->class = 0;
		return 0;
	}
	return -1;
}