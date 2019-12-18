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
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  get () ; 
 int /*<<< orphan*/  maybe_skip_comma () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/  node2s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * peek () ; 
 int /*<<< orphan*/ * read_assignment_expr () ; 
 int /*<<< orphan*/  warnt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skip_to_brace() {
    for (;;) {
        if (next_token('}'))
            return;
        if (next_token('.')) {
            get();
            expect('=');
        }
        Token *tok = peek();
        Node *ignore = read_assignment_expr();
        if (!ignore)
            return;
        warnt(tok, "excessive initializer: %s", node2s(ignore));
        maybe_skip_comma();
    }
}