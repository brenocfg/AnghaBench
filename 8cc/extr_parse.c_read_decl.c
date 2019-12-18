#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_12__ {int isstatic; scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_BODY ; 
 scalar_t__ KIND_FUNC ; 
 int S_EXTERN ; 
 int S_STATIC ; 
 int S_TYPEDEF ; 
 int /*<<< orphan*/  ast_decl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ast_gvar (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * ast_lvar (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ast_typedef (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  copy_incomplete_type (TYPE_1__*) ; 
 int /*<<< orphan*/  ensure_not_void (TYPE_1__*) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  peek () ; 
 int /*<<< orphan*/ * read_decl_init (TYPE_1__*) ; 
 TYPE_1__* read_decl_spec_opt (int*) ; 
 TYPE_1__* read_declarator (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_static_local_var (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * stub1 (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  tok2s (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_decl(Vector *block, bool isglobal) {
    int sclass = 0;
    Type *basetype = read_decl_spec_opt(&sclass);
    if (next_token(';'))
        return;
    for (;;) {
        char *name = NULL;
        Type *ty = read_declarator(&name, copy_incomplete_type(basetype), NULL, DECL_BODY);
        ty->isstatic = (sclass == S_STATIC);
        if (sclass == S_TYPEDEF) {
            ast_typedef(ty, name);
        } else if (ty->isstatic && !isglobal) {
            ensure_not_void(ty);
            read_static_local_var(ty, name);
        } else {
            ensure_not_void(ty);
            Node *var = (isglobal ? ast_gvar : ast_lvar)(ty, name);
            if (next_token('=')) {
                vec_push(block, ast_decl(var, read_decl_init(ty)));
            } else if (sclass != S_EXTERN && ty->kind != KIND_FUNC) {
                vec_push(block, ast_decl(var, NULL));
            }
        }
        if (next_token(';'))
            return;
        if (!next_token(','))
            errort(peek(), "';' or ',' are expected, but got %s", tok2s(peek()));
    }
}