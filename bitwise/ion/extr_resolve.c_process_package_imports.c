#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t num_names; char** names; scalar_t__ import_all; scalar_t__ is_relative; } ;
struct TYPE_14__ {scalar_t__ name; } ;
struct TYPE_18__ {scalar_t__ kind; char* name; TYPE_2__ import; int /*<<< orphan*/  pos; TYPE_1__ note; } ;
struct TYPE_17__ {size_t num_decls; int always_reachable; int /*<<< orphan*/  path; TYPE_5__** decls; } ;
struct TYPE_16__ {TYPE_4__* package; } ;
typedef  TYPE_3__ Sym ;
typedef  TYPE_4__ Package ;
typedef  TYPE_5__ Decl ;

/* Variables and functions */
 scalar_t__ DECL_IMPORT ; 
 scalar_t__ DECL_NOTE ; 
 int /*<<< orphan*/  SYM_PACKAGE ; 
 scalar_t__ always_name ; 
 int /*<<< orphan*/  buf_free (char*) ; 
 int /*<<< orphan*/  buf_printf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  import_all_package_symbols (TYPE_4__*) ; 
 TYPE_4__* import_package (char*) ; 
 int /*<<< orphan*/  import_package_symbols (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  str_islower (char*) ; 
 int /*<<< orphan*/  sym_global_put (char const*,TYPE_3__*) ; 
 TYPE_3__* sym_new (int /*<<< orphan*/ ,char const*,TYPE_5__*) ; 

void process_package_imports(Package *package) {
    for (size_t i = 0; i < package->num_decls; i++) {
        Decl *decl = package->decls[i];
        if (decl->kind == DECL_NOTE) {
            if (decl->note.name == always_name) {
                package->always_reachable = true;
            }
        } else if (decl->kind == DECL_IMPORT) {
            char *path_buf = NULL;
            if (decl->import.is_relative) {
                buf_printf(path_buf, "%s/", package->path);
            }
            for (size_t k = 0; k < decl->import.num_names; k++) {
                if (!str_islower(decl->import.names[k])) {
                    fatal_error(decl->pos, "Import name must be lower case: '%s'", decl->import.names[k]);
                }
                buf_printf(path_buf, "%s%s", k == 0 ? "" : "/", decl->import.names[k]);
            }
            Package *imported_package = import_package(path_buf);
            if (!imported_package) {
                fatal_error(decl->pos, "Failed to import package '%s'", path_buf);
            }
            buf_free(path_buf);
            import_package_symbols(decl, imported_package);
            if (decl->import.import_all) {
                import_all_package_symbols(imported_package);
            }
            const char *sym_name = decl->name ? decl->name : decl->import.names[decl->import.num_names - 1];
            Sym *sym = sym_new(SYM_PACKAGE, sym_name, decl);
            sym->package = imported_package;
            sym_global_put(sym_name, sym);
        }
    }
}