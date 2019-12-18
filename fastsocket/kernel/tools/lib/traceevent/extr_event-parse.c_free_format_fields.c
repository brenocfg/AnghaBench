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
struct format_field {struct format_field* name; struct format_field* type; struct format_field* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct format_field*) ; 

__attribute__((used)) static void free_format_fields(struct format_field *field)
{
	struct format_field *next;

	while (field) {
		next = field->next;
		free(field->type);
		free(field->name);
		free(field);
		field = next;
	}
}