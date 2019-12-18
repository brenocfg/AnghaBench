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
struct tcf_walker {int stop; scalar_t__ count; scalar_t__ skip; scalar_t__ (* fn ) (struct tcf_proto*,unsigned long,struct tcf_walker*) ;} ;
struct tcf_proto {struct route4_head* root; } ;
struct route4_head {struct route4_bucket** table; } ;
struct route4_filter {struct route4_filter* next; } ;
struct route4_bucket {struct route4_filter** ht; } ;

/* Variables and functions */
 scalar_t__ stub1 (struct tcf_proto*,unsigned long,struct tcf_walker*) ; 

__attribute__((used)) static void route4_walk(struct tcf_proto *tp, struct tcf_walker *arg)
{
	struct route4_head *head = tp->root;
	unsigned h, h1;

	if (head == NULL)
		arg->stop = 1;

	if (arg->stop)
		return;

	for (h = 0; h <= 256; h++) {
		struct route4_bucket *b = head->table[h];

		if (b) {
			for (h1 = 0; h1 <= 32; h1++) {
				struct route4_filter *f;

				for (f = b->ht[h1]; f; f = f->next) {
					if (arg->count < arg->skip) {
						arg->count++;
						continue;
					}
					if (arg->fn(tp, (unsigned long)f, arg) < 0) {
						arg->stop = 1;
						return;
					}
					arg->count++;
				}
			}
		}
	}
}