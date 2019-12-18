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
struct TYPE_7__ {scalar_t__ kind; char* sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Map ;

/* Variables and functions */
 char KELLIPSIS ; 
 scalar_t__ TIDENT ; 
 scalar_t__ TNEWLINE ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/  make_macro_token (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ next (char) ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static bool read_funclike_macro_params(Token *name, Map *param) {
    int pos = 0;
    for (;;) {
        Token *tok = lex();
        if (is_keyword(tok, ')'))
            return false;
        if (pos) {
            if (!is_keyword(tok, ','))
                errort(tok, ", expected, but got %s", tok2s(tok));
            tok = lex();
        }
        if (tok->kind == TNEWLINE)
            errort(name, "missing ')' in macro parameter list");
        if (is_keyword(tok, KELLIPSIS)) {
            map_put(param, "__VA_ARGS__", make_macro_token(pos++, true));
            expect(')');
            return true;
        }
        if (tok->kind != TIDENT)
            errort(tok, "identifier expected, but got %s", tok2s(tok));
        char *arg = tok->sval;
        if (next(KELLIPSIS)) {
            expect(')');
            map_put(param, arg, make_macro_token(pos++, true));
            return true;
        }
        map_put(param, arg, make_macro_token(pos++, false));
    }
}