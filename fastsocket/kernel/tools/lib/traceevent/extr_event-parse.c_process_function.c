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
struct print_arg {int dummy; } ;
struct pevent_function_handler {int dummy; } ;
struct event_format {int /*<<< orphan*/  pevent; } ;
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int EVENT_ERROR ; 
 int /*<<< orphan*/  do_warning (char*,char*) ; 
 struct pevent_function_handler* find_func_handler (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free_token (char*) ; 
 int is_flag_field ; 
 int is_symbolic_field ; 
 int process_dynamic_array (struct event_format*,struct print_arg*,char**) ; 
 int process_flags (struct event_format*,struct print_arg*,char**) ; 
 int process_func_handler (struct event_format*,struct pevent_function_handler*,struct print_arg*,char**) ; 
 int process_hex (struct event_format*,struct print_arg*,char**) ; 
 int process_str (struct event_format*,struct print_arg*,char**) ; 
 int process_symbols (struct event_format*,struct print_arg*,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static enum event_type
process_function(struct event_format *event, struct print_arg *arg,
		 char *token, char **tok)
{
	struct pevent_function_handler *func;

	if (strcmp(token, "__print_flags") == 0) {
		free_token(token);
		is_flag_field = 1;
		return process_flags(event, arg, tok);
	}
	if (strcmp(token, "__print_symbolic") == 0) {
		free_token(token);
		is_symbolic_field = 1;
		return process_symbols(event, arg, tok);
	}
	if (strcmp(token, "__print_hex") == 0) {
		free_token(token);
		return process_hex(event, arg, tok);
	}
	if (strcmp(token, "__get_str") == 0) {
		free_token(token);
		return process_str(event, arg, tok);
	}
	if (strcmp(token, "__get_dynamic_array") == 0) {
		free_token(token);
		return process_dynamic_array(event, arg, tok);
	}

	func = find_func_handler(event->pevent, token);
	if (func) {
		free_token(token);
		return process_func_handler(event, func, arg, tok);
	}

	do_warning("function %s not defined", token);
	free_token(token);
	return EVENT_ERROR;
}