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
 int /*<<< orphan*/  KELLIPSIS ; 
 int /*<<< orphan*/  ast_dest (char*) ; 
 int /*<<< orphan*/  cases ; 
 int /*<<< orphan*/  check_case_duplicates (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/  make_case (int,int,char*) ; 
 char* make_label () ; 
 scalar_t__ next_token (int /*<<< orphan*/ ) ; 
 int read_intexpr () ; 
 int /*<<< orphan*/ * read_label_tail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Node *read_case_label(Token *tok) {
    if (!cases)
        errort(tok, "stray case label");
    char *label = make_label();
    int beg = read_intexpr();
    if (next_token(KELLIPSIS)) {
        int end = read_intexpr();
        expect(':');
        if (beg > end)
            errort(tok, "case region is not in correct order: %d ... %d", beg, end);
        vec_push(cases, make_case(beg, end, label));
    } else {
        expect(':');
        vec_push(cases, make_case(beg, beg, label));
    }
    check_case_duplicates(cases);
    return read_label_tail(ast_dest(label));
}