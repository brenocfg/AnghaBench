#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int boolean_t ;
typedef  int /*<<< orphan*/  KXLDSym ;

/* Variables and functions */
 int /*<<< orphan*/  check (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_sym_is_class_vtable (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_sym_is_metaclass_vtable (int /*<<< orphan*/  const*) ; 

boolean_t
kxld_sym_is_vtable(const KXLDSym *sym)
{
    check(sym);

    return kxld_sym_is_class_vtable(sym) || kxld_sym_is_metaclass_vtable(sym);
}