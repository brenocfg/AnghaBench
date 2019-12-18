#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_15__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Token ;
struct TYPE_16__ {TYPE_1__* ty; } ;
typedef  TYPE_2__ Node ;

/* Variables and functions */
 TYPE_2__* ast_conv (TYPE_1__*,TYPE_2__*) ; 
 TYPE_2__* conv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_assignable (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get () ; 
 scalar_t__ is_flotype (TYPE_1__*) ; 
 scalar_t__ is_inttype (TYPE_1__*) ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/ * make_vector () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  read_assignment_expr () ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ *) ; 
 TYPE_1__* type_double ; 
 TYPE_1__* type_int ; 
 TYPE_1__* vec_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static Vector *read_func_args(Vector *params) {
    Vector *args = make_vector();
    int i = 0;
    for (;;) {
        if (next_token(')')) break;
        Node *arg = conv(read_assignment_expr());
        Type *paramtype;
        if (i < vec_len(params)) {
            paramtype = vec_get(params, i++);
        } else {
            paramtype = is_flotype(arg->ty) ? type_double :
                is_inttype(arg->ty) ? type_int :
                arg->ty;
        }
        ensure_assignable(paramtype, arg->ty);
        if (paramtype->kind != arg->ty->kind)
            arg = ast_conv(paramtype, arg);
        vec_push(args, arg);
        Token *tok = get();
        if (is_keyword(tok, ')')) break;
        if (!is_keyword(tok, ','))
            errort(tok, "unexpected token: '%s'", tok2s(tok));
    }
    return args;
}