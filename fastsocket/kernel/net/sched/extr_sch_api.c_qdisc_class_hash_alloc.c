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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (struct hlist_head*) ; 
 unsigned int PAGE_SIZE ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (unsigned int) ; 
 struct hlist_head* kmalloc (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct hlist_head *qdisc_class_hash_alloc(unsigned int n)
{
	unsigned int size = n * sizeof(struct hlist_head), i;
	struct hlist_head *h;

	if (size <= PAGE_SIZE)
		h = kmalloc(size, GFP_KERNEL);
	else
		h = (struct hlist_head *)
			__get_free_pages(GFP_KERNEL, get_order(size));

	if (h != NULL) {
		for (i = 0; i < n; i++)
			INIT_HLIST_HEAD(&h[i]);
	}
	return h;
}