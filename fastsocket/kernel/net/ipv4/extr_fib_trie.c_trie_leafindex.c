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
struct leaf {int dummy; } ;

/* Variables and functions */
 struct leaf* trie_firstleaf (struct trie*) ; 
 struct leaf* trie_nextleaf (struct leaf*) ; 

__attribute__((used)) static struct leaf *trie_leafindex(struct trie *t, int index)
{
	struct leaf *l = trie_firstleaf(t);

	while (l && index-- > 0)
		l = trie_nextleaf(l);

	return l;
}