#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_11__ {scalar_t__ kind; int bol; int space; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TEOF ; 
 scalar_t__ TNEWLINE ; 
 TYPE_1__* copy_token (TYPE_1__*) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*) ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/ * make_vector () ; 
 int /*<<< orphan*/  read_directive (TYPE_1__*) ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Vector *read_one_arg(Token *ident, bool *end, bool readall) {
    Vector *r = make_vector();
    int level = 0;
    for (;;) {
        Token *tok = lex();
        if (tok->kind == TEOF)
            errort(ident, "unterminated macro argument list");
        if (tok->kind == TNEWLINE)
            continue;
        if (tok->bol && is_keyword(tok, '#')) {
            read_directive(tok);
            continue;
        }
        if (level == 0 && is_keyword(tok, ')')) {
            unget_token(tok);
            *end = true;
            return r;
        }
        if (level == 0 && is_keyword(tok, ',') && !readall)
            return r;
        if (is_keyword(tok, '('))
            level++;
        if (is_keyword(tok, ')'))
            level--;
        // C11 6.10.3p10: Within the macro argument list,
        // newline is considered a normal whitespace character.
        // I don't know why the standard specifies such a minor detail,
        // but the difference of newline and space is observable
        // if you stringize tokens using #.
        if (tok->bol) {
            tok = copy_token(tok);
            tok->bol = false;
            tok->space = true;
        }
        vec_push(r, tok);
    }
}