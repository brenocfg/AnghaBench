#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  name; TYPE_3__* expr; } ;
struct TYPE_9__ {scalar_t__ kind; TYPE_1__ field; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {scalar_t__ kind; int /*<<< orphan*/ * package; } ;
typedef  TYPE_2__ Sym ;
typedef  int /*<<< orphan*/  Package ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 scalar_t__ EXPR_FIELD ; 
 scalar_t__ EXPR_NAME ; 
 scalar_t__ SYM_PACKAGE ; 
 TYPE_2__* get_package_sym (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* resolve_name (int /*<<< orphan*/ ) ; 

Package *try_resolve_package(Expr *expr) {
    if (expr->kind == EXPR_NAME) {
        Sym *sym = resolve_name(expr->name);
        if (sym && sym->kind == SYM_PACKAGE) {
            return sym->package;
        }
    } else if (expr->kind == EXPR_FIELD) {
        Package *package = try_resolve_package(expr->field.expr);
        if (package) {
            Sym *sym = get_package_sym(package, expr->field.name);
            if (sym && sym->kind == SYM_PACKAGE) {
                return sym->package;
            }
        }
    }
    return NULL;
}