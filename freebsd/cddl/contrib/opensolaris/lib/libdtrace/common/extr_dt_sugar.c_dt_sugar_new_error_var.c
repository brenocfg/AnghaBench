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
typedef  int /*<<< orphan*/  dt_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  DT_TOK_PTR ; 
 int /*<<< orphan*/  dt_node_ident (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dt_node_op2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static dt_node_t *
dt_sugar_new_error_var(void)
{
	return (dt_node_op2(DT_TOK_PTR, dt_node_ident(strdup("self")),
	    dt_node_ident(strdup("%error"))));
}