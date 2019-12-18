#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_6__ {char const* external_name; int /*<<< orphan*/  reachable; int /*<<< orphan*/ * type; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Sym ;
typedef  int /*<<< orphan*/  Package ;

/* Variables and functions */
 int /*<<< orphan*/  REACHABLE_NATURAL ; 
 int /*<<< orphan*/  SYM_RESOLVED ; 
 int /*<<< orphan*/  SYM_TYPE ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  builtin_package ; 
 int /*<<< orphan*/ * enter_package (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  leave_package (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reachable_syms ; 
 int /*<<< orphan*/  sorted_syms ; 
 int /*<<< orphan*/  sym_global_put (char const*,TYPE_1__*) ; 
 TYPE_1__* sym_new (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 

Sym *sym_global_tuple(const char *name, Type *type) {
    Sym *sym = sym_new(SYM_TYPE, name, NULL);
    sym->state = SYM_RESOLVED;
    sym->type = type;
    sym->external_name = name;
    Package *old_package = enter_package(builtin_package);
    sym_global_put(name, sym);
    leave_package(old_package);
    buf_push(sorted_syms, sym);
    buf_push(reachable_syms, sym);
    sym->reachable = REACHABLE_NATURAL;
    return sym;
}