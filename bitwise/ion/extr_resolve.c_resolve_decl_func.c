#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Type ;
struct TYPE_7__ {size_t num_params; int /*<<< orphan*/  has_varargs; scalar_t__ varargs_type; scalar_t__ ret_type; TYPE_1__* params; } ;
struct TYPE_8__ {scalar_t__ kind; TYPE_2__ func; int /*<<< orphan*/  pos; } ;
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_3__ Decl ;

/* Variables and functions */
 scalar_t__ DECL_FUNC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_len (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  foreign_name ; 
 int /*<<< orphan*/ * get_decl_note (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * incomplete_decay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intrinsic_name ; 
 scalar_t__ is_array_type (int /*<<< orphan*/ *) ; 
 scalar_t__ is_integer_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * resolve_typespec_strict (scalar_t__,int) ; 
 int /*<<< orphan*/ * type_float ; 
 int /*<<< orphan*/ * type_func (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_int ; 
 scalar_t__ type_rank (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * type_void ; 

Type *resolve_decl_func(Decl *decl) {
    assert(decl->kind == DECL_FUNC);
    bool foreign = get_decl_note(decl, foreign_name) != NULL;
    bool intrinsic = get_decl_note(decl, intrinsic_name) != NULL;
    bool with_const = foreign;
    Type **params = NULL;
    for (size_t i = 0; i < decl->func.num_params; i++) {
        Type *param = resolve_typespec_strict(decl->func.params[i].type, with_const);
        param = incomplete_decay(param);
        complete_type(param);
        if (param == type_void && !foreign) {
            fatal_error(decl->pos, "Function parameter type cannot be void");
        }
        buf_push(params, param);
    }
    Type *ret_type = type_void;
    if (decl->func.ret_type) {
        ret_type = incomplete_decay(resolve_typespec_strict(decl->func.ret_type, with_const));
        complete_type(ret_type);
    }
    if (is_array_type(ret_type)) {
        fatal_error(decl->pos, "Function return type cannot be array");
    }
    Type *varargs_type = type_void;
    if (decl->func.varargs_type) {
        varargs_type = incomplete_decay(resolve_typespec_strict(decl->func.varargs_type, with_const));
        complete_type(varargs_type);
        if (is_integer_type(varargs_type) && type_rank(varargs_type) < type_rank(type_int)) {
            fatal_error(decl->pos, "Integer varargs type must have same or higher rank than int");
        } else if (varargs_type == type_float) {
            fatal_error(decl->pos, "Floating varargs type must be double, not float");
        }
    }
    return type_func(params, buf_len(params), ret_type, intrinsic, decl->func.has_varargs, varargs_type);
}