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
struct TYPE_7__ {int /*<<< orphan*/  sval; int /*<<< orphan*/  space; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ is_keyword (TYPE_1__*,char) ; 
 TYPE_1__* lex () ; 
 int /*<<< orphan*/  read_funclike_macro (TYPE_1__*) ; 
 TYPE_1__* read_ident () ; 
 int /*<<< orphan*/  read_obj_macro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 

__attribute__((used)) static void read_define() {
    Token *name = read_ident();
    Token *tok = lex();
    if (is_keyword(tok, '(') && !tok->space) {
        read_funclike_macro(name);
        return;
    }
    unget_token(tok);
    read_obj_macro(name->sval);
}