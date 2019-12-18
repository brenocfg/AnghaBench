#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ kind; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 int /*<<< orphan*/  TNUMBER ; 
 scalar_t__ TSTRING ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  make_token_pushback (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  parse_pragma_operand (TYPE_1__*) ; 
 TYPE_1__* read_token () ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static void handle_pragma_macro(Token *tmpl) {
    expect('(');
    Token *operand = read_token();
    if (operand->kind != TSTRING)
        errort(operand, "_Pragma takes a string literal, but got %s", tok2s(operand));
    expect(')');
    parse_pragma_operand(operand);
    make_token_pushback(tmpl, TNUMBER, "1");
}