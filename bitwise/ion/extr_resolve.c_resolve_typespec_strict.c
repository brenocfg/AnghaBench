#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_13__ ;

/* Type definitions */
struct TYPE_19__ {size_t num_fields; TYPE_4__** fields; } ;
struct TYPE_18__ {size_t num_args; TYPE_4__* ret; TYPE_4__** args; } ;
struct TYPE_20__ {int kind; char** names; int /*<<< orphan*/  pos; TYPE_3__ tuple; TYPE_2__ func; TYPE_13__* num_elems; struct TYPE_20__* base; int /*<<< orphan*/  num_names; } ;
typedef  TYPE_4__ Typespec ;
typedef  int /*<<< orphan*/  Type ;
struct TYPE_17__ {int i; } ;
struct TYPE_22__ {TYPE_1__ val; int /*<<< orphan*/  type; } ;
struct TYPE_21__ {int /*<<< orphan*/ * type; int /*<<< orphan*/  kind; int /*<<< orphan*/ * package; } ;
struct TYPE_16__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_5__ Sym ;
typedef  int /*<<< orphan*/  Package ;
typedef  TYPE_6__ Operand ;

/* Variables and functions */
 int /*<<< orphan*/  SYM_PACKAGE ; 
 int /*<<< orphan*/  SYM_TYPE ; 
#define  TYPESPEC_ARRAY 133 
#define  TYPESPEC_CONST 132 
#define  TYPESPEC_FUNC 131 
#define  TYPESPEC_NAME 130 
#define  TYPESPEC_PTR 129 
#define  TYPESPEC_TUPLE 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cast_operand (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * current_package ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_5__* get_package_sym (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  get_reachable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * incomplete_decay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_array_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_integer_type (int /*<<< orphan*/ ) ; 
 TYPE_6__ resolve_const_expr (TYPE_13__*) ; 
 int /*<<< orphan*/  resolve_sym (TYPE_5__*) ; 
 int /*<<< orphan*/  set_reachable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_resolved_sym (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  set_resolved_type (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * type_const (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_func (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_int ; 
 int /*<<< orphan*/ * type_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_tuple (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * type_void ; 

Type *resolve_typespec_strict(Typespec *typespec, bool with_const) {
    if (!typespec) {
        return type_void;
    }
    Type *result = NULL;
    switch (typespec->kind) {
    case TYPESPEC_NAME: {
        Package *package = current_package;
        for (size_t i = 0; i < typespec->num_names - 1; i++) {
            const char *name = typespec->names[i];
            Sym *sym = get_package_sym(package, name);
            if (!sym) {
                fatal_error(typespec->pos, "Unresolved package '%s'", name);
            }
            if (sym->kind != SYM_PACKAGE) {
                fatal_error(typespec->pos, "%s must denote a package", name);
                return NULL;
            }
            package = sym->package;
        }
        const char *name = typespec->names[typespec->num_names - 1];
        Sym *sym = get_package_sym(package, name);
        if (!sym) {
            fatal_error(typespec->pos, "Unresolved type name '%s'", name);
        }
        if (sym->kind != SYM_TYPE) {
            fatal_error(typespec->pos, "%s must denote a type", name);
            return NULL;
        }
        resolve_sym(sym);
        set_resolved_sym(typespec, sym);
        result = sym->type;
        break;
    }
    case TYPESPEC_CONST:
        result = resolve_typespec_strict(typespec->base, with_const);
        if (with_const) {
            result = type_const(result);
        }
        break;
    case TYPESPEC_PTR:
        result = type_ptr(resolve_typespec_strict(typespec->base, with_const));
        break;
    case TYPESPEC_ARRAY: {
        int size = 0;
        Type *base = resolve_typespec_strict(typespec->base, with_const);
        if (typespec->num_elems) {
            Operand operand = resolve_const_expr(typespec->num_elems);
            if (!is_integer_type(operand.type)) {
                fatal_error(typespec->pos, "Array size constant expression must have integer type");
            }
            cast_operand(&operand, type_int);
            size = operand.val.i;
            if (size < 0) {
                fatal_error(typespec->num_elems->pos, "Non-positive array size");
            }
        }
        result = type_array(base, size, typespec->num_elems == NULL);
        break;
    }
    case TYPESPEC_FUNC: {
        Type **args = NULL;
        for (size_t i = 0; i < typespec->func.num_args; i++) {
            Type *arg = resolve_typespec_strict(typespec->func.args[i], with_const);
            if (arg == type_void) {
                fatal_error(typespec->pos, "Function parameter type cannot be void");
            }
            arg = incomplete_decay(arg);
            buf_push(args, arg);
        }
        Type *ret = type_void;
        if (typespec->func.ret) {
            ret = incomplete_decay(resolve_typespec_strict(typespec->func.ret, with_const));
        }
        if (is_array_type(ret)) {
            fatal_error(typespec->pos, "Function return type cannot be array");
        }
        // TODO: func pointers should be able to support varargs (including typed)
        result = type_func(args, buf_len(args), ret, false, false, type_void);
        break;
    }
    case TYPESPEC_TUPLE: {
        Type **fields = NULL;
        for (size_t i = 0; i < typespec->tuple.num_fields; i++) {
            Type *field = resolve_typespec_strict(typespec->tuple.fields[i], with_const);
            if (field == type_void) {
                fatal_error(typespec->pos, "Tuple element types cannot be void");
            }
            buf_push(fields, field);
        }
        result = type_tuple(fields, buf_len(fields));
        if (!get_reachable(result)) {
            set_reachable(result);
        }
        break;
    }
    default:
        assert(0);
        return NULL;
    }
    set_resolved_type(typespec, result);
    return result;
}