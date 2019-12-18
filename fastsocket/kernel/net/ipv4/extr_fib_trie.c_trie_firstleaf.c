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
struct trie {int /*<<< orphan*/  trie; } ;
struct tnode {int dummy; } ;
struct leaf {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_LEAF (struct tnode*) ; 
 struct leaf* leaf_walk_rcu (struct tnode*,int /*<<< orphan*/ *) ; 
 scalar_t__ rcu_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct leaf *trie_firstleaf(struct trie *t)
{
	struct tnode *n = (struct tnode *) rcu_dereference(t->trie);

	if (!n)
		return NULL;

	if (IS_LEAF(n))          /* trie is just a leaf */
		return (struct leaf *) n;

	return leaf_walk_rcu(n, NULL);
}