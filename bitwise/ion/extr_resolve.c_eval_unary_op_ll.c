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
typedef  int TokenKind ;

/* Variables and functions */
#define  TOKEN_ADD 131 
#define  TOKEN_NEG 130 
#define  TOKEN_NOT 129 
#define  TOKEN_SUB 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

long long eval_unary_op_ll(TokenKind op, long long val) {
    switch (op) {
    case TOKEN_ADD:
        return +val;
    case TOKEN_SUB:
        return -val;
    case TOKEN_NEG:
        return ~val;
    case TOKEN_NOT:
        return !val;
    default:
        assert(0);
        break;
    }
    return 0;
}