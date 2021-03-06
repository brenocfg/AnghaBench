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
typedef  int /*<<< orphan*/  ast_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ast_pending () ; 

void
ast_off(ast_t reasons)
{
	ast_t *pending_ast = ast_pending();

	*pending_ast &= ~reasons;
}