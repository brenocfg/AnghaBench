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
struct TYPE_6__ {scalar_t__ state; scalar_t__ kind; int /*<<< orphan*/  type; TYPE_1__* decl; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_incomplete; } ;
typedef  TYPE_2__ Sym ;

/* Variables and functions */
 scalar_t__ SYM_FUNC ; 
 scalar_t__ SYM_RESOLVED ; 
 scalar_t__ SYM_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  complete_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_func_body (TYPE_2__*) ; 

void finalize_sym(Sym *sym) {
    assert(sym->state == SYM_RESOLVED);
    if (sym->decl && !sym->decl->is_incomplete) {
        if (sym->kind == SYM_TYPE) {
            complete_type(sym->type);
        } else if (sym->kind == SYM_FUNC) {
            resolve_func_body(sym);
        }
    }
}