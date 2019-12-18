#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
typedef  int /*<<< orphan*/  Type ;
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 char KELLIPSIS ; 
 char KVOID ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * get () ; 
 scalar_t__ is_keyword (int /*<<< orphan*/ *,char) ; 
 scalar_t__ is_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_func_type (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * make_vector () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/ * peek () ; 
 int /*<<< orphan*/  read_declarator_params (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  read_declarator_params_oldstyle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  type_int ; 
 int /*<<< orphan*/  unget_token (int /*<<< orphan*/ *) ; 
 int vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Type *read_func_param_list(Vector *paramvars, Type *rettype) {
    // C11 6.7.6.3p10: A parameter list with just "void" specifies that
    // the function has no parameters.
    Token *tok = get();
    if (is_keyword(tok, KVOID) && next_token(')'))
        return make_func_type(rettype, make_vector(), false, false);

    // C11 6.7.6.3p14: K&R-style un-prototyped declaration or
    // function definition having no parameters.
    // We return a type representing K&R-style declaration here.
    // If this is actually part of a declartion, the type will be fixed later.
    if (is_keyword(tok, ')'))
        return make_func_type(rettype, make_vector(), true, true);
    unget_token(tok);

    Token *tok2 = peek();
    if (next_token(KELLIPSIS))
        errort(tok2, "at least one parameter is required before \"...\"");
    if (is_type(peek())) {
        bool ellipsis;
        Vector *paramtypes = make_vector();
        read_declarator_params(paramtypes, paramvars, &ellipsis);
        return make_func_type(rettype, paramtypes, ellipsis, false);
    }
    if (!paramvars)
        errort(tok, "invalid function definition");
    read_declarator_params_oldstyle(paramvars);
    Vector *paramtypes = make_vector();
    for (int i = 0; i < vec_len(paramvars); i++)
        vec_push(paramtypes, type_int);
    return make_func_type(rettype, paramtypes, false, true);
}