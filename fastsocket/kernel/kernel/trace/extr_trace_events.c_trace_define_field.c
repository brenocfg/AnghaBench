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
struct ftrace_event_field {int filter_type; int offset; int size; int is_signed; struct ftrace_event_field* type; struct ftrace_event_field* name; int /*<<< orphan*/  link; } ;
struct ftrace_event_call {int /*<<< orphan*/  fields; } ;

/* Variables and functions */
 int ENOMEM ; 
 int FILTER_OTHER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int filter_assign_type (char const*) ; 
 int /*<<< orphan*/  kfree (struct ftrace_event_field*) ; 
 void* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 struct ftrace_event_field* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int trace_define_field(struct ftrace_event_call *call, const char *type,
		       const char *name, int offset, int size, int is_signed,
		       int filter_type)
{
	struct ftrace_event_field *field;

	field = kzalloc(sizeof(*field), GFP_KERNEL);
	if (!field)
		goto err;

	field->name = kstrdup(name, GFP_KERNEL);
	if (!field->name)
		goto err;

	field->type = kstrdup(type, GFP_KERNEL);
	if (!field->type)
		goto err;

	if (filter_type == FILTER_OTHER)
		field->filter_type = filter_assign_type(type);
	else
		field->filter_type = filter_type;

	field->offset = offset;
	field->size = size;
	field->is_signed = is_signed;

	list_add(&field->link, &call->fields);

	return 0;

err:
	if (field) {
		kfree(field->name);
		kfree(field->type);
	}
	kfree(field);

	return -ENOMEM;
}