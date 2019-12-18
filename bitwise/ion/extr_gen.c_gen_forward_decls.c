#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  typeid; } ;
typedef  TYPE_1__ Type ;
struct TYPE_15__ {int kind; } ;
struct TYPE_14__ {TYPE_3__* decl; } ;
typedef  TYPE_2__ Sym ;
typedef  TYPE_3__ Decl ;

/* Variables and functions */
#define  DECL_STRUCT 129 
#define  DECL_UNION 128 
 TYPE_2__** buf_end (TYPE_2__**) ; 
 int buf_len (TYPE_1__**) ; 
 int /*<<< orphan*/  genlnf (char*,char*,char const*,...) ; 
 char* get_gen_name (TYPE_2__*) ; 
 scalar_t__ is_decl_foreign (TYPE_3__*) ; 
 int /*<<< orphan*/  is_sym_reachable (TYPE_2__*) ; 
 scalar_t__ is_tuple_reachable (TYPE_1__*) ; 
 TYPE_2__** sorted_syms ; 
 TYPE_1__** tuple_types ; 

void gen_forward_decls(void) {
    for (int i = 0; i < buf_len(tuple_types); i++) {
        Type *type = tuple_types[i];
        if (is_tuple_reachable(type)) {
            genlnf("typedef struct tuple%d tuple%d;", type->typeid, type->typeid);
        }
    }
    for (Sym **it = sorted_syms; it != buf_end(sorted_syms); it++) {
        Sym *sym = *it;
        Decl *decl = sym->decl;
        if (!decl || !is_sym_reachable(sym)) {
            continue;
        }
        if (is_decl_foreign(decl)) {
            continue;
        }
        switch (decl->kind) {
        case DECL_STRUCT:
        case DECL_UNION: {
            const char *name = get_gen_name(sym);
            genlnf("typedef %s %s %s;", decl->kind == DECL_STRUCT ? "struct" : "union", name, name);
            break;
        }
        default:
            // Do nothing.
            break;
        }
    }
}