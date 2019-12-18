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
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 char* gen_buf ; 
 int /*<<< orphan*/  gen_expr (int /*<<< orphan*/ *) ; 

const char *gen_expr_str(Expr *expr) {
    char *temp = gen_buf;
    gen_buf = NULL;
    gen_expr(expr);
    const char *result = gen_buf;
    gen_buf = temp;
    return result;
}