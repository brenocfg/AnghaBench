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

/* Variables and functions */
 int /*<<< orphan*/  TOKEN_ADD ; 
 int /*<<< orphan*/  TOKEN_AND ; 
 int /*<<< orphan*/  TOKEN_DEC ; 
 int /*<<< orphan*/  TOKEN_INC ; 
 int /*<<< orphan*/  TOKEN_MUL ; 
 int /*<<< orphan*/  TOKEN_NEG ; 
 int /*<<< orphan*/  TOKEN_NOT ; 
 int /*<<< orphan*/  TOKEN_SUB ; 
 scalar_t__ is_token (int /*<<< orphan*/ ) ; 

bool is_unary_op(void) {
    return
        is_token(TOKEN_ADD) ||
        is_token(TOKEN_SUB) ||
        is_token(TOKEN_MUL) ||
        is_token(TOKEN_AND) ||
        is_token(TOKEN_NEG) ||
        is_token(TOKEN_NOT) ||
        is_token(TOKEN_INC) ||
        is_token(TOKEN_DEC);
}