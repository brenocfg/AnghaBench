#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct symbol {int dummy; } ;
struct TYPE_4__ {struct symbol* sym; } ;
struct TYPE_3__ {struct symbol* sym; } ;
struct expr {int type; TYPE_2__ right; TYPE_1__ left; } ;
typedef  enum expr_type { ____Placeholder_expr_type } expr_type ;

/* Variables and functions */
 struct expr* calloc (int,int) ; 

struct expr *expr_alloc_comp(enum expr_type type, struct symbol *s1, struct symbol *s2)
{
	struct expr *e = calloc(1, sizeof(*e));
	e->type = type;
	e->left.sym = s1;
	e->right.sym = s2;
	return e;
}