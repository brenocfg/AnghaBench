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
struct property {int length; void* value; int /*<<< orphan*/  name; } ;
struct cc_workarea {int name_offset; int prop_length; int prop_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dlpar_free_cc_property (struct property*) ; 
 int /*<<< orphan*/  kstrdup (char*,int /*<<< orphan*/ ) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,char*,int) ; 

__attribute__((used)) static struct property *dlpar_parse_cc_property(struct cc_workarea *ccwa)
{
	struct property *prop;
	char *name;
	char *value;

	prop = kzalloc(sizeof(*prop), GFP_KERNEL);
	if (!prop)
		return NULL;

	name = (char *)ccwa + ccwa->name_offset;
	prop->name = kstrdup(name, GFP_KERNEL);
	if (!prop->name) {
		dlpar_free_cc_property(prop);
		return NULL;
	}

	prop->length = ccwa->prop_length;
	value = (char *)ccwa + ccwa->prop_offset;
	prop->value = kzalloc(prop->length, GFP_KERNEL);
	if (!prop->value) {
		dlpar_free_cc_property(prop);
		return NULL;
	}

	memcpy(prop->value, value, prop->length);
	return prop;
}