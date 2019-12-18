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
 int /*<<< orphan*/  ABS (int) ; 
 int /*<<< orphan*/  DT_TOK_PTR ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dt_node_ident (char*) ; 
 int /*<<< orphan*/ * dt_node_op2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 

__attribute__((used)) static dt_node_t *
dt_sugar_new_condition_var(int condid)
{
	char *str;

	if (condid == 0)
		return (NULL);
	assert(condid > 0);

	(void) asprintf(&str, "%%condition_%d", ABS(condid));
	return (dt_node_op2(DT_TOK_PTR, dt_node_ident(strdup("this")),
	    dt_node_ident(str)));
}