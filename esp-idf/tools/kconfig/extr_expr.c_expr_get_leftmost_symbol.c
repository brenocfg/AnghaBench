#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct expr* expr; } ;
struct expr {scalar_t__ type; TYPE_1__ left; } ;

/* Variables and functions */
 scalar_t__ E_SYMBOL ; 
 struct expr* expr_copy (struct expr const*) ; 

__attribute__((used)) static inline struct expr *
expr_get_leftmost_symbol(const struct expr *e)
{

	if (e == NULL)
		return NULL;

	while (e->type != E_SYMBOL)
		e = e->left.expr;

	return expr_copy(e);
}