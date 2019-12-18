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
struct TYPE_2__ {scalar_t__ len; int /*<<< orphan*/  val; } ;
struct property {TYPE_1__ val; struct property* name; struct property* next; } ;
struct node {int /*<<< orphan*/  fullpath; int /*<<< orphan*/  basenamelen; int /*<<< orphan*/  name; struct property* proplist; } ;
struct dt_info {int dummy; } ;
struct check {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAIL (struct check*,struct dt_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_free (TYPE_1__) ; 
 int /*<<< orphan*/  free (struct property*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ streq (struct property*,char*) ; 

__attribute__((used)) static void check_name_properties(struct check *c, struct dt_info *dti,
				  struct node *node)
{
	struct property **pp, *prop = NULL;

	for (pp = &node->proplist; *pp; pp = &((*pp)->next))
		if (streq((*pp)->name, "name")) {
			prop = *pp;
			break;
		}

	if (!prop)
		return; /* No name property, that's fine */

	if ((prop->val.len != node->basenamelen+1)
	    || (memcmp(prop->val.val, node->name, node->basenamelen) != 0)) {
		FAIL(c, dti, "\"name\" property in %s is incorrect (\"%s\" instead"
		     " of base node name)", node->fullpath, prop->val.val);
	} else {
		/* The name property is correct, and therefore redundant.
		 * Delete it */
		*pp = prop->next;
		free(prop->name);
		data_free(prop->val);
		free(prop);
	}
}