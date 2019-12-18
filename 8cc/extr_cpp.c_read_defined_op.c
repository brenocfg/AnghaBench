#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ kind; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 TYPE_1__* cpp_token_one ; 
 TYPE_1__* cpp_token_zero ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/  macros ; 
 scalar_t__ map_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static Token *read_defined_op() {
    Token *tok = lex();
    if (is_keyword(tok, '(')) {
        tok = lex();
        expect(')');
    }
    if (tok->kind != TIDENT)
        errort(tok, "identifier expected, but got %s", tok2s(tok));
    return map_get(macros, tok->sval) ? cpp_token_one : cpp_token_zero;
}