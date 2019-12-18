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
struct rb_node {int dummy; } ;

/* Variables and functions */
 struct rb_node* __key_user_next (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_next (struct rb_node*) ; 

__attribute__((used)) static struct rb_node *key_user_next(struct rb_node *n)
{
	return __key_user_next(rb_next(n));
}