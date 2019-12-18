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
struct tnode {struct tnode* tnode_free; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int sync_pages ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 int /*<<< orphan*/  tnode_free (struct tnode*) ; 
 struct tnode* tnode_free_head ; 
 int tnode_free_size ; 

__attribute__((used)) static void tnode_free_flush(void)
{
	struct tnode *tn;

	while ((tn = tnode_free_head)) {
		tnode_free_head = tn->tnode_free;
		tn->tnode_free = NULL;
		tnode_free(tn);
	}

	if (tnode_free_size >= PAGE_SIZE * sync_pages) {
		tnode_free_size = 0;
		synchronize_rcu();
	}
}