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
struct TYPE_7__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TEOF ; 
 scalar_t__ TIDENT ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__* get () ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 scalar_t__ is_type (TYPE_1__*) ; 
 int /*<<< orphan*/ * make_vector () ; 
 TYPE_1__* peek () ; 
 int /*<<< orphan*/  skip_parentheses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unget_token (int /*<<< orphan*/ ) ; 
 scalar_t__ vec_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static bool is_funcdef() {
    Vector *buf = make_vector();
    bool r = false;
    for (;;) {
        Token *tok = get();
        vec_push(buf, tok);
        if (tok->kind == TEOF)
            error("premature end of input");
        if (is_keyword(tok, ';'))
            break;
        if (is_type(tok))
            continue;
        if (is_keyword(tok, '(')) {
            skip_parentheses(buf);
            continue;
        }
        if (tok->kind != TIDENT)
            continue;
        if (!is_keyword(peek(), '('))
            continue;
        vec_push(buf, get());
        skip_parentheses(buf);
        r = (is_keyword(peek(), '{') || is_type(peek()));
        break;
    }
    while (vec_len(buf) > 0)
        unget_token(vec_pop(buf));
    return r;
}