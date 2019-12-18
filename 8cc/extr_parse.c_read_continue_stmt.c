#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * ast_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  lcontinue ; 

__attribute__((used)) static Node *read_continue_stmt(Token *tok) {
    expect(';');
    if (!lcontinue)
        errort(tok, "stray continue statement");
    return ast_jump(lcontinue);
}