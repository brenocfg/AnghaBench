#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t num_args; int has_varargs; TYPE_2__* ret; int /*<<< orphan*/  args; } ;
struct TYPE_9__ {TYPE_1__ func; } ;
typedef  TYPE_2__ Typespec ;
typedef  int /*<<< orphan*/  SrcPos ;

/* Variables and functions */
 int /*<<< orphan*/  AST_DUP (TYPE_2__**) ; 
 int /*<<< orphan*/  TYPESPEC_FUNC ; 
 TYPE_2__* new_typespec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Typespec *new_typespec_func(SrcPos pos, Typespec **args, size_t num_args, Typespec *ret, bool has_varargs) {
    Typespec *t = new_typespec(TYPESPEC_FUNC, pos);
    t->func.args = AST_DUP(args);
    t->func.num_args = num_args;
    t->func.ret = ret;
    t->func.has_varargs = has_varargs;
    return t;
}