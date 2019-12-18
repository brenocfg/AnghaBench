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
 int GFP_KERNEL ; 
 unsigned long PAGE_SIZE ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (unsigned long) ; 
 struct hlist_head* kzalloc (unsigned long,int) ; 

__attribute__((used)) static struct hlist_head *fz_hash_alloc(int divisor)
{
	unsigned long size = divisor * sizeof(struct hlist_head);

	if (size <= PAGE_SIZE) {
		return kzalloc(size, GFP_KERNEL);
	} else {
		return (struct hlist_head *)
			__get_free_pages(GFP_KERNEL | __GFP_ZERO, get_order(size));
	}
}