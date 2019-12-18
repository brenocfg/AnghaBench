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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  ENC_NONE ; 
 int /*<<< orphan*/ * ast_func (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ast_string (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/ * current_func_type ; 
 int /*<<< orphan*/ * localenv ; 
 int /*<<< orphan*/ * localvars ; 
 int /*<<< orphan*/ * make_map_parent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_compound_stmt () ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static Node *read_func_body(Type *functype, char *fname, Vector *params) {
    localenv = make_map_parent(localenv);
    localvars = make_vector();
    current_func_type = functype;
    Node *funcname = ast_string(ENC_NONE, fname, strlen(fname) + 1);
    map_put(localenv, "__func__", funcname);
    map_put(localenv, "__FUNCTION__", funcname);
    Node *body = read_compound_stmt();
    Node *r = ast_func(functype, fname, params, body, localvars);
    current_func_type = NULL;
    localenv = NULL;
    localvars = NULL;
    return r;
}