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
struct hlist_head {int dummy; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (unsigned int) ; 
 int /*<<< orphan*/  kfree (struct hlist_head*) ; 

__attribute__((used)) static void qdisc_class_hash_free(struct hlist_head *h, unsigned int n)
{
	unsigned int size = n * sizeof(struct hlist_head);

	if (size <= PAGE_SIZE)
		kfree(h);
	else
		free_pages((unsigned long)h, get_order(size));
}