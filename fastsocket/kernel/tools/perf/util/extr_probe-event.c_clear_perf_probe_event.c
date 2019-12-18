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
struct perf_probe_point {struct perf_probe_arg_field* lazy_line; struct perf_probe_arg_field* function; struct perf_probe_arg_field* file; } ;
struct perf_probe_event {int nargs; struct perf_probe_arg_field* args; struct perf_probe_arg_field* group; struct perf_probe_arg_field* event; struct perf_probe_point point; } ;
struct perf_probe_arg_field {struct perf_probe_arg_field* name; struct perf_probe_arg_field* next; struct perf_probe_arg_field* field; struct perf_probe_arg_field* type; struct perf_probe_arg_field* var; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct perf_probe_arg_field*) ; 
 int /*<<< orphan*/  memset (struct perf_probe_event*,int /*<<< orphan*/ ,int) ; 

void clear_perf_probe_event(struct perf_probe_event *pev)
{
	struct perf_probe_point *pp = &pev->point;
	struct perf_probe_arg_field *field, *next;
	int i;

	if (pev->event)
		free(pev->event);
	if (pev->group)
		free(pev->group);
	if (pp->file)
		free(pp->file);
	if (pp->function)
		free(pp->function);
	if (pp->lazy_line)
		free(pp->lazy_line);
	for (i = 0; i < pev->nargs; i++) {
		if (pev->args[i].name)
			free(pev->args[i].name);
		if (pev->args[i].var)
			free(pev->args[i].var);
		if (pev->args[i].type)
			free(pev->args[i].type);
		field = pev->args[i].field;
		while (field) {
			next = field->next;
			if (field->name)
				free(field->name);
			free(field);
			field = next;
		}
	}
	if (pev->args)
		free(pev->args);
	memset(pev, 0, sizeof(*pev));
}