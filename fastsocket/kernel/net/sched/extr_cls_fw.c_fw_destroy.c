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
struct tcf_proto {struct fw_head* root; } ;
struct fw_head {struct fw_filter** ht; } ;
struct fw_filter {struct fw_filter* next; } ;

/* Variables and functions */
 int HTSIZE ; 
 int /*<<< orphan*/  fw_delete_filter (struct tcf_proto*,struct fw_filter*) ; 
 int /*<<< orphan*/  kfree (struct fw_head*) ; 

__attribute__((used)) static void fw_destroy(struct tcf_proto *tp)
{
	struct fw_head *head = tp->root;
	struct fw_filter *f;
	int h;

	if (head == NULL)
		return;

	for (h=0; h<HTSIZE; h++) {
		while ((f=head->ht[h]) != NULL) {
			head->ht[h] = f->next;
			fw_delete_filter(tp, f);
		}
	}
	kfree(head);
}