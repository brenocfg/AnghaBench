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
struct property {int /*<<< orphan*/ * name; } ;
struct node {int /*<<< orphan*/  fullpath; } ;
struct check {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int strspn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_property_name_chars(struct check *c, struct node *dt,
				      struct node *node, struct property *prop)
{
	int n = strspn(prop->name, c->data);

	if (n < strlen(prop->name))
		FAIL(c, "Bad character '%c' in property name \"%s\", node %s",
		     prop->name[n], prop->name, node->fullpath);
}