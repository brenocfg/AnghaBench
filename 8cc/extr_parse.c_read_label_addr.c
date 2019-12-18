#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kind; int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 scalar_t__ TIDENT ; 
 int /*<<< orphan*/ * ast_label_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errort (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get () ; 
 int /*<<< orphan*/  gotos ; 
 int /*<<< orphan*/  tok2s (TYPE_1__*) ; 
 int /*<<< orphan*/  vec_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static Node *read_label_addr(Token *tok) {
    // [GNU] Labels as values. You can get the address of the a label
    // with unary "&&" operator followed by a label name.
    Token *tok2 = get();
    if (tok2->kind != TIDENT)
        errort(tok, "label name expected after &&, but got %s", tok2s(tok2));
    Node *r = ast_label_addr(tok2->sval);
    vec_push(gotos, r);
    return r;
}