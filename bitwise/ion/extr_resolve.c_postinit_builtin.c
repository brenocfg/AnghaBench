#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ kind; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Sym ;

/* Variables and functions */
 scalar_t__ SYM_TYPE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ builtin_package ; 
 scalar_t__ current_package ; 
 TYPE_1__* resolve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_intern (char*) ; 
 int /*<<< orphan*/  type_allocator ; 
 int /*<<< orphan*/  type_allocator_ptr ; 
 int /*<<< orphan*/  type_ptr (int /*<<< orphan*/ ) ; 

void postinit_builtin(void) {
    assert(current_package == builtin_package);
    Sym *sym = resolve_name(str_intern("Allocator"));
    if (sym) {
        assert(sym->kind == SYM_TYPE);
        type_allocator = sym->type;
        type_allocator_ptr = type_ptr(type_allocator);
    }
}