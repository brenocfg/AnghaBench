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
typedef  int /*<<< orphan*/  Package ;

/* Variables and functions */
 int /*<<< orphan*/  add_package_decls (int /*<<< orphan*/ *) ; 
 int buf_len (int /*<<< orphan*/ ) ; 
 scalar_t__ builtin_package ; 
 int /*<<< orphan*/ * enter_package (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  import_all_package_symbols (scalar_t__) ; 
 int /*<<< orphan*/  init_builtin_syms () ; 
 int /*<<< orphan*/  leave_package (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  package_list ; 
 int /*<<< orphan*/  parse_package (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_package_imports (int /*<<< orphan*/ *) ; 

bool compile_package(Package *package) {
    if (!parse_package(package)) {
        return false;
    }
    Package *old_package = enter_package(package);
    if (buf_len(package_list) == 1) {
        init_builtin_syms();
    }
    if (builtin_package) {
        import_all_package_symbols(builtin_package);
    }
    add_package_decls(package);
    process_package_imports(package);
    leave_package(old_package);
    return true;
}