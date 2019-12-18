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
struct tcf_proto {struct route4_head* root; } ;
struct route4_head {struct route4_filter** ht; struct route4_head** table; } ;
struct route4_filter {struct route4_filter* next; } ;
struct route4_bucket {struct route4_filter** ht; struct route4_bucket** table; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct route4_head*) ; 
 int /*<<< orphan*/  route4_delete_filter (struct tcf_proto*,struct route4_filter*) ; 

__attribute__((used)) static void route4_destroy(struct tcf_proto *tp)
{
	struct route4_head *head = tp->root;
	int h1, h2;

	if (head == NULL)
		return;

	for (h1=0; h1<=256; h1++) {
		struct route4_bucket *b;

		if ((b = head->table[h1]) != NULL) {
			for (h2=0; h2<=32; h2++) {
				struct route4_filter *f;

				while ((f = b->ht[h2]) != NULL) {
					b->ht[h2] = f->next;
					route4_delete_filter(tp, f);
				}
			}
			kfree(b);
		}
	}
	kfree(head);
}