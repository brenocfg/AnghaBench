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
struct TYPE_5__ {scalar_t__ kind; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;

/* Variables and functions */
 scalar_t__ TSTRING ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* get () ; 
 int read_intexpr () ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 

__attribute__((used)) static void read_static_assert() {
    expect('(');
    int val = read_intexpr();
    expect(',');
    Token *tok = get();
    if (tok->kind != TSTRING)
        errort(tok, "string expected as the second argument for _Static_assert, but got %s", tok2s(tok));
    expect(')');
    expect(';');
    if (!val)
        errort(tok, "_Static_assert failure: %s", tok->sval);
}