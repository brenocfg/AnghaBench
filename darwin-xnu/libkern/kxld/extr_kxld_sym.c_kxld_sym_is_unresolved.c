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
 scalar_t__ kxld_sym_is_common (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_sym_is_indirect (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  kxld_sym_is_replaced (int /*<<< orphan*/  const*) ; 
 scalar_t__ kxld_sym_is_undefined (int /*<<< orphan*/  const*) ; 

boolean_t
kxld_sym_is_unresolved(const KXLDSym *sym)
{
    return ((kxld_sym_is_undefined(sym) && !kxld_sym_is_replaced(sym)) ||
            kxld_sym_is_indirect(sym) || kxld_sym_is_common(sym));
}