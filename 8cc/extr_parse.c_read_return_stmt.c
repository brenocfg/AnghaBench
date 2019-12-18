#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rettype; } ;
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/ * ast_conv (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ast_return (int /*<<< orphan*/ *) ; 
 TYPE_1__* current_func_type ; 
 int /*<<< orphan*/  expect (char) ; 
 int /*<<< orphan*/ * read_expr_opt () ; 

__attribute__((used)) static Node *read_return_stmt() {
    Node *retval = read_expr_opt();
    expect(';');
    if (retval)
        return ast_return(ast_conv(current_func_type->rettype, retval));
    return ast_return(NULL);
}