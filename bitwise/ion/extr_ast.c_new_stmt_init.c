#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_5__ {char const* name; int is_undef; int /*<<< orphan*/ * expr; int /*<<< orphan*/ * type; } ;
struct TYPE_6__ {TYPE_1__ init; } ;
typedef  TYPE_2__ Stmt ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  STMT_INIT ; 
 TYPE_2__* new_stmt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Stmt *new_stmt_init(SrcPos pos, const char *name, Typespec *type, Expr *expr, bool is_undef) {
    Stmt *s = new_stmt(STMT_INIT, pos);
    s->init.name = name;
    s->init.type = type;
    s->init.expr = expr;
    s->init.is_undef = is_undef;
    return s;
}