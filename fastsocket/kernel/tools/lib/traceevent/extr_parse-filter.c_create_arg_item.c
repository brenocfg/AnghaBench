#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct format_field {int dummy; } ;
struct TYPE_6__ {struct format_field* field; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {int /*<<< orphan*/  val; int /*<<< orphan*/  type; int /*<<< orphan*/  str; } ;
struct filter_arg {TYPE_3__ field; void* type; TYPE_2__ boolean; TYPE_1__ value; } ;
struct event_format {int dummy; } ;
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int /*<<< orphan*/  COMM ; 
#define  EVENT_DQUOTE 130 
#define  EVENT_ITEM 129 
#define  EVENT_SQUOTE 128 
 void* FILTER_ARG_BOOLEAN ; 
 void* FILTER_ARG_FIELD ; 
 void* FILTER_ARG_VALUE ; 
 int /*<<< orphan*/  FILTER_CHAR ; 
 int /*<<< orphan*/  FILTER_FALSE ; 
 int /*<<< orphan*/  FILTER_NUMBER ; 
 int /*<<< orphan*/  FILTER_STRING ; 
 struct filter_arg* allocate_arg () ; 
 struct format_field comm ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  free_arg (struct filter_arg*) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 struct format_field* pevent_find_any_field (struct event_format*,char const*) ; 
 int /*<<< orphan*/  show_error (char**,char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strtoull (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct filter_arg *
create_arg_item(struct event_format *event, const char *token,
		enum event_type type, char **error_str)
{
	struct format_field *field;
	struct filter_arg *arg;

	arg = allocate_arg();

	switch (type) {

	case EVENT_SQUOTE:
	case EVENT_DQUOTE:
		arg->type = FILTER_ARG_VALUE;
		arg->value.type =
			type == EVENT_DQUOTE ? FILTER_STRING : FILTER_CHAR;
		arg->value.str = strdup(token);
		if (!arg->value.str)
			die("malloc string");
		break;
	case EVENT_ITEM:
		/* if it is a number, then convert it */
		if (isdigit(token[0])) {
			arg->type = FILTER_ARG_VALUE;
			arg->value.type = FILTER_NUMBER;
			arg->value.val = strtoull(token, NULL, 0);
			break;
		}
		/* Consider this a field */
		field = pevent_find_any_field(event, token);
		if (!field) {
			if (strcmp(token, COMM) != 0) {
				/* not a field, Make it false */
				arg->type = FILTER_ARG_BOOLEAN;
				arg->boolean.value = FILTER_FALSE;
				break;
			}
			/* If token is 'COMM' then it is special */
			field = &comm;
		}
		arg->type = FILTER_ARG_FIELD;
		arg->field.field = field;
		break;
	default:
		free_arg(arg);
		show_error(error_str, "expected a value but found %s",
			   token);
		return NULL;
	}
	return arg;
}