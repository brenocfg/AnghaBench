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
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 int /*<<< orphan*/  current_package ; 
 int /*<<< orphan*/ * get_package_sym (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * sym_get_local (char const*) ; 

Sym *sym_get(const char *name) {
    Sym *sym = sym_get_local(name);
    return sym ? sym : get_package_sym(current_package, name);
}