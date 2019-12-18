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
#define  TOKEN_ADD 143 
#define  TOKEN_AND 142 
#define  TOKEN_DIV 141 
#define  TOKEN_EQ 140 
#define  TOKEN_GT 139 
#define  TOKEN_GTEQ 138 
#define  TOKEN_LSHIFT 137 
#define  TOKEN_LT 136 
#define  TOKEN_LTEQ 135 
#define  TOKEN_MOD 134 
#define  TOKEN_MUL 133 
#define  TOKEN_NOTEQ 132 
#define  TOKEN_OR 131 
#define  TOKEN_RSHIFT 130 
#define  TOKEN_SUB 129 
#define  TOKEN_XOR 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

unsigned long long eval_binary_op_ull(TokenKind op, unsigned long long left, unsigned long long right) {
    switch (op) {
    case TOKEN_MUL:
        return left * right;
    case TOKEN_DIV:
        return right != 0 ? left / right : 0;
    case TOKEN_MOD:
        return right != 0 ? left % right : 0;
    case TOKEN_AND:
        return left & right;
    case TOKEN_LSHIFT:
        return left << right;
    case TOKEN_RSHIFT:
        return left >> right;
    case TOKEN_ADD:
        return left + right;
    case TOKEN_SUB:
        return left - right;
    case TOKEN_OR:
        return left | right;
    case TOKEN_XOR:
        return left ^ right;
    case TOKEN_EQ:
        return left == right;
    case TOKEN_NOTEQ:
        return left != right;
    case TOKEN_LT:
        return left < right;
    case TOKEN_LTEQ:
        return left <= right;
    case TOKEN_GT:
        return left > right;
    case TOKEN_GTEQ:
        return left >= right;
    default:
        assert(0);
        break;
    }
    return 0;
}