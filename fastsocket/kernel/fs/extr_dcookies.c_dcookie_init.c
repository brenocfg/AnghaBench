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
struct list_head {int dummy; } ;
struct dcookie_struct {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  dcookie_cache ; 
 struct list_head* dcookie_hashtable ; 
 unsigned int hash_size ; 
 struct list_head* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dcookie_init(void)
{
	struct list_head * d;
	unsigned int i, hash_bits;
	int err = -ENOMEM;

	dcookie_cache = kmem_cache_create("dcookie_cache",
		sizeof(struct dcookie_struct),
		0, 0, NULL);

	if (!dcookie_cache)
		goto out;

	dcookie_hashtable = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!dcookie_hashtable)
		goto out_kmem;

	err = 0;

	/*
	 * Find the power-of-two list-heads that can fit into the allocation..
	 * We don't guarantee that "sizeof(struct list_head)" is necessarily
	 * a power-of-two.
	 */
	hash_size = PAGE_SIZE / sizeof(struct list_head);
	hash_bits = 0;
	do {
		hash_bits++;
	} while ((hash_size >> hash_bits) != 0);
	hash_bits--;

	/*
	 * Re-calculate the actual number of entries and the mask
	 * from the number of bits we can fit.
	 */
	hash_size = 1UL << hash_bits;

	/* And initialize the newly allocated array */
	d = dcookie_hashtable;
	i = hash_size;
	do {
		INIT_LIST_HEAD(d);
		d++;
		i--;
	} while (i);

out:
	return err;
out_kmem:
	kmem_cache_destroy(dcookie_cache);
	goto out;
}