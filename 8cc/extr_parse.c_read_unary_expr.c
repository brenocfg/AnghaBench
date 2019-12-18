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
struct TYPE_7__ {scalar_t__ kind; int id; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
#define  KALIGNOF 132 
#define  KSIZEOF 131 
#define  OP_DEC 130 
#define  OP_INC 129 
#define  OP_LOGAND 128 
 int /*<<< orphan*/  OP_PRE_DEC ; 
 int /*<<< orphan*/  OP_PRE_INC ; 
 scalar_t__ TKEYWORD ; 
 TYPE_1__* get () ; 
 int /*<<< orphan*/ * read_alignof_operand () ; 
 int /*<<< orphan*/ * read_cast_expr () ; 
 int /*<<< orphan*/ * read_label_addr (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_postfix_expr () ; 
 int /*<<< orphan*/ * read_sizeof_operand () ; 
 int /*<<< orphan*/ * read_unary_addr () ; 
 int /*<<< orphan*/ * read_unary_bitnot (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_unary_deref (TYPE_1__*) ; 
 int /*<<< orphan*/ * read_unary_incdec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * read_unary_lognot () ; 
 int /*<<< orphan*/ * read_unary_minus () ; 
 int /*<<< orphan*/  unget_token (TYPE_1__*) ; 

__attribute__((used)) static Node *read_unary_expr() {
    Token *tok = get();
    if (tok->kind == TKEYWORD) {
        switch (tok->id) {
        case KSIZEOF: return read_sizeof_operand();
        case KALIGNOF: return read_alignof_operand();
        case OP_INC: return read_unary_incdec(OP_PRE_INC);
        case OP_DEC: return read_unary_incdec(OP_PRE_DEC);
        case OP_LOGAND: return read_label_addr(tok);
        case '&': return read_unary_addr();
        case '*': return read_unary_deref(tok);
        case '+': return read_cast_expr();
        case '-': return read_unary_minus();
        case '~': return read_unary_bitnot(tok);
        case '!': return read_unary_lognot();
        }
    }
    unget_token(tok);
    return read_postfix_expr();
}