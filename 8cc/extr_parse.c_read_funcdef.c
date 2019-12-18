#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_7__ {int hasva; int isstatic; int /*<<< orphan*/  params; scalar_t__ oldstyle; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_BODY ; 
 int S_STATIC ; 
 int /*<<< orphan*/  ast_gvar (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  backfill_labels () ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  globalenv ; 
 void* gotos ; 
 int /*<<< orphan*/  labels ; 
 int /*<<< orphan*/ * localenv ; 
 int /*<<< orphan*/  make_map () ; 
 int /*<<< orphan*/ * make_map_parent (int /*<<< orphan*/ ) ; 
 void* make_vector () ; 
 int /*<<< orphan*/  param_types (int /*<<< orphan*/ *) ; 
 TYPE_1__* read_decl_spec_opt (int*) ; 
 TYPE_1__* read_declarator (char**,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_func_body (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_oldstyle_param_type (int /*<<< orphan*/ *) ; 
 scalar_t__ vec_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_funcdef() {
    int sclass = 0;
    Type *basetype = read_decl_spec_opt(&sclass);
    localenv = make_map_parent(globalenv);
    gotos = make_vector();
    labels = make_map();
    char *name;
    Vector *params = make_vector();
    Type *functype = read_declarator(&name, basetype, params, DECL_BODY);
    if (functype->oldstyle) {
        if (vec_len(params) == 0)
            functype->hasva = false;
        read_oldstyle_param_type(params);
        functype->params = param_types(params);
    }
    functype->isstatic = (sclass == S_STATIC);
    ast_gvar(functype, name);
    expect('{');
    Node *r = read_func_body(functype, name, params);
    backfill_labels();
    localenv = NULL;
    return r;
}