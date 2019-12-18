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
struct context {scalar_t__ len; int /*<<< orphan*/ * str; scalar_t__ type; scalar_t__ role; scalar_t__ user; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mls_context_destroy (struct context*) ; 

__attribute__((used)) static inline void context_destroy(struct context *c)
{
	c->user = c->role = c->type = 0;
	kfree(c->str);
	c->str = NULL;
	c->len = 0;
	mls_context_destroy(c);
}