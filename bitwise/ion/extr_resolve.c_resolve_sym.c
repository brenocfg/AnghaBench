#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_15__ {int /*<<< orphan*/  type; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_17__ {scalar_t__ kind; scalar_t__ is_incomplete; int /*<<< orphan*/  pos; TYPE_2__ enum_decl; TYPE_1__ typedef_decl; } ;
struct TYPE_16__ {scalar_t__ state; int kind; int /*<<< orphan*/  type; int /*<<< orphan*/  val; int /*<<< orphan*/  home_package; TYPE_4__* decl; scalar_t__ reachable; } ;
typedef  TYPE_3__ Sym ;
typedef  int /*<<< orphan*/  Package ;
typedef  TYPE_4__ Decl ;

/* Variables and functions */
 scalar_t__ DECL_ENUM ; 
 scalar_t__ DECL_STRUCT ; 
 scalar_t__ DECL_TYPEDEF ; 
 scalar_t__ DECL_UNION ; 
#define  SYM_CONST 132 
#define  SYM_FUNC 131 
#define  SYM_PACKAGE 130 
 scalar_t__ SYM_RESOLVED ; 
 scalar_t__ SYM_RESOLVING ; 
#define  SYM_TYPE 129 
 scalar_t__ SYM_UNRESOLVED ; 
#define  SYM_VAR 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * enter_package (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  is_decl_foreign (TYPE_4__*) ; 
 int /*<<< orphan*/  is_integer_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_local_sym (TYPE_3__*) ; 
 int /*<<< orphan*/  leave_package (int /*<<< orphan*/ *) ; 
 scalar_t__ reachable_phase ; 
 int /*<<< orphan*/  reachable_syms ; 
 int /*<<< orphan*/  resolve_decl_const (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolve_decl_func (TYPE_4__*) ; 
 int /*<<< orphan*/  resolve_decl_var (TYPE_4__*) ; 
 int /*<<< orphan*/ * resolve_typespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_typespec_strict (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sorted_syms ; 
 int /*<<< orphan*/  type_enum (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_incomplete (TYPE_3__*) ; 
 int /*<<< orphan*/ * type_int ; 

void resolve_sym(Sym *sym) {
    if (sym->state == SYM_RESOLVED) {
        return;
    } else if (sym->state == SYM_RESOLVING) {
        fatal_error(sym->decl->pos, "Cyclic dependency");
        return;
    }
    assert(sym->state == SYM_UNRESOLVED);
    assert(!sym->reachable);
    if (!is_local_sym(sym)) {
        buf_push(reachable_syms, sym);
        sym->reachable = reachable_phase;
    }
    sym->state = SYM_RESOLVING;
    Decl *decl = sym->decl;
    Package *old_package = enter_package(sym->home_package);
    switch (sym->kind) {
    case SYM_TYPE:
        if (decl && decl->kind == DECL_TYPEDEF) {
            sym->type = resolve_typespec_strict(decl->typedef_decl.type, is_decl_foreign(decl));
        } else if (decl->kind == DECL_ENUM) {
            Type *base = decl->enum_decl.type ? resolve_typespec(decl->enum_decl.type) : type_int;
            if (!is_integer_type(base)) {
                fatal_error(decl->pos, "Base type of enum must be integer type");
            }
            sym->type = type_enum(sym, base);
        } else {
            sym->type = type_incomplete(sym);
        }
        break;
    case SYM_VAR:
        sym->type = resolve_decl_var(decl);
        break;
    case SYM_CONST:
        sym->type = resolve_decl_const(decl, &sym->val);
        break;
    case SYM_FUNC:
        sym->type = resolve_decl_func(decl);
        break;
    case SYM_PACKAGE:
        // Do nothing
        break;
    default:
        assert(0);
        break;
    }
    leave_package(old_package);
    sym->state = SYM_RESOLVED;
    if (decl->is_incomplete || (decl->kind != DECL_STRUCT && decl->kind != DECL_UNION)) {
        buf_push(sorted_syms, sym);
    }
}