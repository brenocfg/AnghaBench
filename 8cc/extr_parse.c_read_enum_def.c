#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Type ;
struct TYPE_14__ {scalar_t__ kind; char* sval; } ;
typedef  TYPE_2__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ KIND_ENUM ; 
 scalar_t__ TIDENT ; 
 int /*<<< orphan*/ * ast_inttype (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  env () ; 
 int /*<<< orphan*/  errort (TYPE_2__*,char*,char*) ; 
 TYPE_2__* get () ; 
 scalar_t__ is_keyword (TYPE_2__*,char) ; 
 TYPE_1__* map_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ next_token (char) ; 
 TYPE_2__* peek () ; 
 int read_intexpr () ; 
 int /*<<< orphan*/  tags ; 
 char* tok2s (TYPE_2__*) ; 
 int /*<<< orphan*/ * type_enum ; 
 TYPE_1__* type_int ; 
 int /*<<< orphan*/  unget_token (TYPE_2__*) ; 

__attribute__((used)) static Type *read_enum_def() {
    char *tag = NULL;
    Token *tok = get();

    // Enum is handled as a synonym for int. We only check if the enum
    // is declared.
    if (tok->kind == TIDENT) {
        tag = tok->sval;
        tok = get();
    }
    if (tag) {
        Type *ty = map_get(tags, tag);
        if (ty && ty->kind != KIND_ENUM)
            errort(tok, "declarations of %s does not match", tag);
    }
    if (!is_keyword(tok, '{')) {
        if (!tag || !map_get(tags, tag))
            errort(tok, "enum tag %s is not defined", tag);
        unget_token(tok);
        return type_int;
    }
    if (tag)
        map_put(tags, tag, type_enum);

    int val = 0;
    for (;;) {
        tok = get();
        if (is_keyword(tok, '}'))
            break;
        if (tok->kind != TIDENT)
            errort(tok, "identifier expected, but got %s", tok2s(tok));
        char *name = tok->sval;

        if (next_token('='))
            val = read_intexpr();
        Node *constval = ast_inttype(type_int, val++);
        map_put(env(), name, constval);
        if (next_token(','))
            continue;
        if (next_token('}'))
            break;
        errort(peek(), "',' or '}' expected, but got %s", tok2s(peek()));
    }
    return type_int;
}