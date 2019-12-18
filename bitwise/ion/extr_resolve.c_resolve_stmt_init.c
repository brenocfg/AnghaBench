#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  is_undef; int /*<<< orphan*/  expr; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  pos; TYPE_1__ init; } ;
typedef  TYPE_2__ Stmt ;

/* Variables and functions */
 scalar_t__ STMT_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * resolve_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_push_var (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void resolve_stmt_init(Stmt *stmt) {
    assert(stmt->kind == STMT_INIT);
    Type *type = resolve_init(stmt->pos, stmt->init.type, stmt->init.expr, false, stmt->init.is_undef);
    if (!sym_push_var(stmt->init.name, type)) {
        fatal_error(stmt->pos, "Shadowed definition of local symbol");
    }
}