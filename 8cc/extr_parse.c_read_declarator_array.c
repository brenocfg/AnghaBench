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
typedef  TYPE_1__ Type ;
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 scalar_t__ KIND_FUNC ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* make_array_type (TYPE_1__*,int) ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/ * peek () ; 
 TYPE_1__* read_declarator_tail (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int read_intexpr () ; 

__attribute__((used)) static Type *read_declarator_array(Type *basety) {
    int len;
    if (next_token(']')) {
        len = -1;
    } else {
        len = read_intexpr();
        expect(']');
    }
    Token *tok = peek();
    Type *t = read_declarator_tail(basety, NULL);
    if (t->kind == KIND_FUNC)
        errort(tok, "array of functions");
    return make_array_type(t, len);
}