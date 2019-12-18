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
struct device_node {int /*<<< orphan*/  full_name; } ;
struct cc_workarea {int name_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct device_node*) ; 
 int /*<<< orphan*/  kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct device_node* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static struct device_node *dlpar_parse_cc_node(struct cc_workarea *ccwa)
{
	struct device_node *dn;
	char *name;

	dn = kzalloc(sizeof(*dn), GFP_KERNEL);
	if (!dn)
		return NULL;

	/* The configure connector reported name does not contain a
	 * preceeding '/', so we allocate a buffer large enough to
	 * prepend this to the full_name.
	 */
	name = (char *)ccwa + ccwa->name_offset;
	dn->full_name = kmalloc(strlen(name) + 2, GFP_KERNEL);
	if (!dn->full_name) {
		kfree(dn);
		return NULL;
	}

	sprintf(dn->full_name, "/%s", name);
	return dn;
}