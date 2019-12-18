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
struct TYPE_6__ {char const* name; int /*<<< orphan*/  home_package; int /*<<< orphan*/ * decl; int /*<<< orphan*/  kind; } ;
typedef  int /*<<< orphan*/  SymKind ;
typedef  TYPE_1__ Sym ;
typedef  int /*<<< orphan*/  Decl ;

/* Variables and functions */
 int /*<<< orphan*/  current_package ; 
 int /*<<< orphan*/  set_resolved_sym (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* xcalloc (int,int) ; 

Sym *sym_new(SymKind kind, const char *name, Decl *decl) {
    Sym *sym = xcalloc(1, sizeof(Sym));
    sym->kind = kind;
    sym->name = name;
    sym->decl = decl;
    sym->home_package = current_package;
    set_resolved_sym(sym, sym);
    return sym;
}