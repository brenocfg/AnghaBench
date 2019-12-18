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
struct symbol {int dummy; } ;
struct TYPE_2__ {struct symbol* sym; } ;
struct expr {TYPE_1__ left; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_SYMBOL ; 
 struct expr* malloc (int) ; 
 int /*<<< orphan*/  memset (struct expr*,int /*<<< orphan*/ ,int) ; 

struct expr *expr_alloc_symbol(struct symbol *sym)
{
	struct expr *e = malloc(sizeof(*e));
	memset(e, 0, sizeof(*e));
	e->type = E_SYMBOL;
	e->left.sym = sym;
	return e;
}