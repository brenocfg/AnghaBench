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
 scalar_t__ TIDENT ; 
 scalar_t__ TNEWLINE ; 
 TYPE_1__* cpp_token_zero ; 
 scalar_t__ is_ident (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * make_vector () ; 
 TYPE_1__* read_defined_op () ; 
 TYPE_1__* read_expand_newline () ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Vector *read_intexpr_line() {
    Vector *r = make_vector();
    for (;;) {
        Token *tok = read_expand_newline();
        if (tok->kind == TNEWLINE)
            return r;
        if (is_ident(tok, "defined")) {
            vec_push(r, read_defined_op());
        } else if (tok->kind == TIDENT) {
            // C11 6.10.1.4 says that remaining identifiers
            // should be replaced with pp-number 0.
            vec_push(r, cpp_token_zero);
        } else {
            vec_push(r, tok);
        }
    }
}