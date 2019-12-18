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
struct tnode {scalar_t__ pos; scalar_t__ bits; } ;
struct node {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_LEAF (struct node const*) ; 

__attribute__((used)) static inline int tnode_full(const struct tnode *tn, const struct node *n)
{
	if (n == NULL || IS_LEAF(n))
		return 0;

	return ((struct tnode *) n)->pos == tn->pos + tn->bits;
}