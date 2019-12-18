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
struct TYPE_7__ {scalar_t__ kind; TYPE_2__* sym; } ;
typedef  TYPE_1__ Type ;
struct TYPE_9__ {scalar_t__ kind; int /*<<< orphan*/  aggregate; int /*<<< orphan*/  pos; scalar_t__ is_incomplete; } ;
struct TYPE_8__ {TYPE_3__* decl; int /*<<< orphan*/  home_package; } ;
typedef  TYPE_2__ Sym ;
typedef  int /*<<< orphan*/  Package ;
typedef  TYPE_3__ Decl ;

/* Variables and functions */
 scalar_t__ DECL_STRUCT ; 
 scalar_t__ DECL_UNION ; 
 scalar_t__ TYPE_COMPLETING ; 
 scalar_t__ TYPE_INCOMPLETE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  complete_aggregate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * enter_package (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  leave_package (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sorted_syms ; 

void complete_type(Type *type) {
    if (type->kind == TYPE_COMPLETING) {
        fatal_error(type->sym->decl->pos, "Type completion cycle");
        return;
    } else if (type->kind != TYPE_INCOMPLETE) {
        return;
    }
    Sym *sym = type->sym;
    Package *old_package = enter_package(sym->home_package);
    Decl *decl = sym->decl;
    if (decl->is_incomplete) {
        fatal_error(decl->pos, "Trying to use incomplete type as complete type");
    }
    type->kind = TYPE_COMPLETING;
    assert(decl->kind == DECL_STRUCT || decl->kind == DECL_UNION);
    complete_aggregate(type, decl->aggregate);
    buf_push(sorted_syms, type->sym);
    leave_package(old_package);
}