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
struct node {int /*<<< orphan*/  fullpath; int /*<<< orphan*/ * name; } ;
struct dt_info {int dummy; } ;
struct check {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,struct dt_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int strspn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_node_name_chars(struct check *c, struct dt_info *dti,
				  struct node *node)
{
	int n = strspn(node->name, c->data);

	if (n < strlen(node->name))
		FAIL(c, dti, "Bad character '%c' in node %s",
		     node->name[n], node->fullpath);
}