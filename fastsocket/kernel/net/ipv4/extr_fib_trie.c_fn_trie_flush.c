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
struct trie {int dummy; } ;
struct leaf {int /*<<< orphan*/  list; } ;
struct fib_table {scalar_t__ tb_data; } ;

/* Variables and functions */
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct leaf* trie_firstleaf (struct trie*) ; 
 scalar_t__ trie_flush_leaf (struct leaf*) ; 
 int /*<<< orphan*/  trie_leaf_remove (struct trie*,struct leaf*) ; 
 struct leaf* trie_nextleaf (struct leaf*) ; 

__attribute__((used)) static int fn_trie_flush(struct fib_table *tb)
{
	struct trie *t = (struct trie *) tb->tb_data;
	struct leaf *l, *ll = NULL;
	int found = 0;

	for (l = trie_firstleaf(t); l; l = trie_nextleaf(l)) {
		found += trie_flush_leaf(l);

		if (ll && hlist_empty(&ll->list))
			trie_leaf_remove(t, ll);
		ll = l;
	}

	if (ll && hlist_empty(&ll->list))
		trie_leaf_remove(t, ll);

	pr_debug("trie_flush found=%d\n", found);
	return found;
}