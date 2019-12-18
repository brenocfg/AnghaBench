#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ expr; scalar_t__ type; } ;
struct TYPE_13__ {int /*<<< orphan*/  block; } ;
struct TYPE_16__ {scalar_t__ kind; TYPE_2__ var; TYPE_1__ func; scalar_t__ is_incomplete; } ;
struct TYPE_15__ {scalar_t__ state; scalar_t__ reachable; int /*<<< orphan*/  type; TYPE_4__* decl; } ;
typedef  TYPE_3__ Sym ;
typedef  TYPE_4__ Decl ;

/* Variables and functions */
 scalar_t__ DECL_FUNC ; 
 scalar_t__ DECL_VAR ; 
 scalar_t__ REACHABLE_NATURAL ; 
 scalar_t__ SYM_RESOLVED ; 
 TYPE_3__** buf_end (TYPE_3__**) ; 
 char* gen_buf ; 
 int /*<<< orphan*/  gen_expr (scalar_t__) ; 
 int /*<<< orphan*/  gen_func_decl (TYPE_4__*) ; 
 int /*<<< orphan*/  gen_stmt_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genf (char*) ; 
 int /*<<< orphan*/  genln () ; 
 int /*<<< orphan*/  genlnf (char*,...) ; 
 scalar_t__ get_decl_note (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_gen_name (TYPE_3__*) ; 
 int /*<<< orphan*/  inline_name ; 
 int is_decl_foreign (TYPE_4__*) ; 
 scalar_t__ is_decl_threadlocal (TYPE_4__*) ; 
 int /*<<< orphan*/  is_incomplete_array_typespec (scalar_t__) ; 
 TYPE_3__** sorted_syms ; 
 int /*<<< orphan*/  str_intern (char*) ; 
 int /*<<< orphan*/  type_to_cdecl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  typespec_to_cdecl (scalar_t__,int /*<<< orphan*/ ) ; 

void gen_defs(void) {
    for (Sym **it = sorted_syms; it != buf_end(sorted_syms); it++) {
        Sym *sym = *it;
        Decl *decl = sym->decl;
        if (sym->state != SYM_RESOLVED || !decl || decl->is_incomplete || sym->reachable != REACHABLE_NATURAL) {
            continue;
        }
        if (decl->kind == DECL_FUNC) {
            bool foreign = is_decl_foreign(decl);;
            char *buf = gen_buf;
            if (foreign) {
                gen_buf = NULL;
            }
            if (get_decl_note(decl, inline_name)) {
                genlnf("INLINE");
            }
            if (get_decl_note(decl, str_intern("noinline"))) {
                genlnf("NOINLINE");
            }
            gen_func_decl(decl);
            genf(" ");
            gen_stmt_block(decl->func.block);
            genln();
            if (foreign) {
                gen_buf = buf;
            }
        } else if (decl->kind == DECL_VAR) {
            if (is_decl_threadlocal(decl)) {
                genlnf("THREADLOCAL");
            }
            if (decl->var.type && !is_incomplete_array_typespec(decl->var.type)) {
                genlnf("%s", typespec_to_cdecl(decl->var.type, get_gen_name(sym)));
            } else {
                genlnf("%s", type_to_cdecl(sym->type, get_gen_name(sym)));
            }
            if (decl->var.expr) {
                genf(" = ");
                gen_expr(decl->var.expr);
            }
            genf(";");
        }
    }
}