#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int /*<<< orphan*/  type; int /*<<< orphan*/  expr; } ;
struct TYPE_17__ {int kind; TYPE_4__ enum_decl; TYPE_3__ typedef_decl; int /*<<< orphan*/  type; TYPE_2__ var; TYPE_1__ const_decl; int /*<<< orphan*/  pos; struct TYPE_17__* decl; } ;
typedef  TYPE_5__ Sym ;
typedef  TYPE_5__ Decl ;

/* Variables and functions */
#define  DECL_CONST 135 
#define  DECL_ENUM 134 
#define  DECL_FUNC 133 
#define  DECL_IMPORT 132 
#define  DECL_STRUCT 131 
#define  DECL_TYPEDEF 130 
#define  DECL_UNION 129 
#define  DECL_VAR 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_aggregate (TYPE_5__*) ; 
 int /*<<< orphan*/  gen_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_func_decl (TYPE_5__*) ; 
 int /*<<< orphan*/  gen_sync_pos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genf (char*,...) ; 
 int /*<<< orphan*/  genln () ; 
 int /*<<< orphan*/  genlnf (char*,...) ; 
 char* get_gen_name (TYPE_5__*) ; 
 scalar_t__ is_decl_foreign (TYPE_5__*) ; 
 int /*<<< orphan*/  is_decl_threadlocal (TYPE_5__*) ; 
 int /*<<< orphan*/  is_incomplete_array_typespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_to_cdecl (int /*<<< orphan*/ ,char*) ; 
 char* typespec_to_cdecl (int /*<<< orphan*/ ,char*) ; 

void gen_decl(Sym *sym) {
    Decl *decl = sym->decl;
    if (!decl || is_decl_foreign(decl)) {
        return;
    }
    gen_sync_pos(decl->pos);
    switch (decl->kind) {
    case DECL_CONST:
        genlnf("#define %s (", get_gen_name(sym));
        if (decl->const_decl.type) {
            genf("(%s)(", typespec_to_cdecl(decl->const_decl.type, ""));
        }
        gen_expr(decl->const_decl.expr);
        if (decl->const_decl.type) {
            genf(")");
        }
        genf(")");
        break;
    case DECL_VAR:
        if (is_decl_threadlocal(decl)) {
            genlnf("THREADLOCAL");
        }
        genlnf("extern ");
        if (decl->var.type && !is_incomplete_array_typespec(decl->var.type)) {
            genf("%s", typespec_to_cdecl(decl->var.type, get_gen_name(sym)));
        } else {
            genf("%s", type_to_cdecl(sym->type, get_gen_name(sym)));
        }
        genf(";");
        break;
    case DECL_FUNC:
        gen_func_decl(decl);
        genf(";");
        break;
    case DECL_STRUCT:
    case DECL_UNION:
        gen_aggregate(decl);
        break;
    case DECL_TYPEDEF:
        genlnf("typedef %s;", typespec_to_cdecl(decl->typedef_decl.type, get_gen_name(sym)));
        break;
    case DECL_ENUM:
        if (decl->enum_decl.type) {
            genlnf("typedef %s;", typespec_to_cdecl(decl->enum_decl.type, get_gen_name(decl)));
        } else {
            genlnf("typedef int %s;", get_gen_name(decl));
        }
        break;
    case DECL_IMPORT:
        // Do nothing
        break;
    default:
        assert(0);
        break;
    }
    genln();
}