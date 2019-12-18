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
struct TYPE_9__ {scalar_t__ kind; int id; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
#define  KBREAK 138 
#define  KCASE 137 
#define  KCONTINUE 136 
#define  KDEFAULT 135 
#define  KDO 134 
#define  KFOR 133 
#define  KGOTO 132 
#define  KIF 131 
#define  KRETURN 130 
#define  KSWITCH 129 
#define  KWHILE 128 
 scalar_t__ TIDENT ; 
 scalar_t__ TKEYWORD ; 
 int /*<<< orphan*/  expect (char) ; 
 TYPE_1__* get () ; 
 scalar_t__ next_token (char) ; 
 int /*<<< orphan*/ * read_break_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_case_label (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_compound_stmt () ; 
 int /*<<< orphan*/ * read_continue_stmt (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_default_label (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_do_stmt () ; 
 int /*<<< orphan*/ * read_expr_opt () ; 
 int /*<<< orphan*/ * read_for_stmt () ; 
 int /*<<< orphan*/ * read_goto_stmt () ; 
 int /*<<< orphan*/ * read_if_stmt () ; 
 int /*<<< orphan*/ * read_label (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_return_stmt () ; 
 int /*<<< orphan*/ * read_switch_stmt () ; 
 int /*<<< orphan*/ * read_while_stmt () ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 

__attribute__((used)) static Node *read_stmt() {
    Token *tok = get();
    if (tok->kind == TKEYWORD) {
        switch (tok->id) {
        case '{':       return read_compound_stmt();
        case KIF:       return read_if_stmt();
        case KFOR:      return read_for_stmt();
        case KWHILE:    return read_while_stmt();
        case KDO:       return read_do_stmt();
        case KRETURN:   return read_return_stmt();
        case KSWITCH:   return read_switch_stmt();
        case KCASE:     return read_case_label(tok);
        case KDEFAULT:  return read_default_label(tok);
        case KBREAK:    return read_break_stmt(tok);
        case KCONTINUE: return read_continue_stmt(tok);
        case KGOTO:     return read_goto_stmt();
        }
    }
    if (tok->kind == TIDENT && next_token(':'))
        return read_label(tok);
    unget_token(tok);
    Node *r = read_expr_opt();
    expect(';');
    return r;
}