#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TEOF ; 
 int /*<<< orphan*/  error (char*) ; 
 TYPE_1__* get () ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void skip_parentheses(Vector *buf) {
    for (;;) {
        Token *tok = get();
        if (tok->kind == TEOF)
            error("premature end of input");
        vec_push(buf, tok);
        if (is_keyword(tok, ')'))
            return;
        if (is_keyword(tok, '('))
            skip_parentheses(buf);
    }
}