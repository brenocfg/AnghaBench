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
typedef  int u32 ;
struct tcf_proto {scalar_t__ root; } ;
struct route4_head {struct route4_bucket** table; } ;
struct route4_filter {int handle; struct route4_filter* next; } ;
struct route4_bucket {struct route4_filter** ht; } ;

/* Variables and functions */
 unsigned int from_hash (int) ; 
 unsigned int to_hash (int) ; 

__attribute__((used)) static unsigned long route4_get(struct tcf_proto *tp, u32 handle)
{
	struct route4_head *head = (struct route4_head*)tp->root;
	struct route4_bucket *b;
	struct route4_filter *f;
	unsigned h1, h2;

	if (!head)
		return 0;

	h1 = to_hash(handle);
	if (h1 > 256)
		return 0;

	h2 = from_hash(handle>>16);
	if (h2 > 32)
		return 0;

	if ((b = head->table[h1]) != NULL) {
		for (f = b->ht[h2]; f; f = f->next)
			if (f->handle == handle)
				return (unsigned long)f;
	}
	return 0;
}