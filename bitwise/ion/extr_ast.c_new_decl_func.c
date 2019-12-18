#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Typespec ;
struct TYPE_5__ {size_t num_params; int has_varargs; int /*<<< orphan*/  block; int /*<<< orphan*/ * varargs_type; int /*<<< orphan*/ * ret_type; int /*<<< orphan*/  params; } ;
struct TYPE_6__ {TYPE_1__ func; } ;
typedef  int /*<<< orphan*/  StmtList ;
typedef  int /*<<< orphan*/  SrcPos ;
typedef  int /*<<< orphan*/  FuncParam ;
typedef  TYPE_2__ Decl ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DECL_FUNC ; 
 TYPE_2__* new_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

Decl *new_decl_func(SrcPos pos, const char *name, FuncParam *params, size_t num_params, Typespec *ret_type, bool has_varargs, Typespec *varargs_type, StmtList block) {
    Decl *d = new_decl(DECL_FUNC, pos, name);
    d->func.params = AST_DUP(params);
    d->func.num_params = num_params;
    d->func.ret_type = ret_type;
    d->func.has_varargs = has_varargs;
    d->func.varargs_type = varargs_type;
    d->func.block = block;
    return d;
}