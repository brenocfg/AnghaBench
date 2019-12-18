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
 int /*<<< orphan*/  ast_dest (scalar_t__) ; 
 scalar_t__ defaultcase ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  expect (char) ; 
 scalar_t__ make_label () ; 
 int /*<<< orphan*/ * read_label_tail (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *read_default_label(Token *tok) {
    expect(':');
    if (defaultcase)
        errort(tok, "duplicate default");
    defaultcase = make_label();
    return read_label_tail(ast_dest(defaultcase));
}