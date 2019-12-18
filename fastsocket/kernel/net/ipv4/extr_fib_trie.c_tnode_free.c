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
struct tnode {int /*<<< orphan*/  rcu; } ;
struct leaf {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_LEAF (struct tnode*) ; 
 int /*<<< orphan*/  __tnode_free_rcu ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_leaf (struct leaf*) ; 

__attribute__((used)) static inline void tnode_free(struct tnode *tn)
{
	if (IS_LEAF(tn))
		free_leaf((struct leaf *) tn);
	else
		call_rcu(&tn->rcu, __tnode_free_rcu);
}