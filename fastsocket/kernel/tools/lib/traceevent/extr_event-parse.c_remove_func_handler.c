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
struct pevent_function_handler {struct pevent_function_handler* next; int /*<<< orphan*/  name; } ;
struct pevent {struct pevent_function_handler* func_handlers; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_func_handle (struct pevent_function_handler*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void remove_func_handler(struct pevent *pevent, char *func_name)
{
	struct pevent_function_handler *func;
	struct pevent_function_handler **next;

	next = &pevent->func_handlers;
	while ((func = *next)) {
		if (strcmp(func->name, func_name) == 0) {
			*next = func->next;
			free_func_handle(func);
			break;
		}
		next = &func->next;
	}
}