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
struct pevent_record {int dummy; } ;
struct TYPE_2__ {int type; int /*<<< orphan*/  reg; int /*<<< orphan*/  val; int /*<<< orphan*/ * field; } ;
struct filter_arg {TYPE_1__ str; } ;
struct event_format {int dummy; } ;

/* Variables and functions */
#define  FILTER_CMP_MATCH 131 
#define  FILTER_CMP_NOT_MATCH 130 
#define  FILTER_CMP_NOT_REGEX 129 
#define  FILTER_CMP_REGEX 128 
 int /*<<< orphan*/  comm ; 
 char* get_comm (struct event_format*,struct pevent_record*) ; 
 char* get_field_str (struct filter_arg*,struct pevent_record*) ; 
 int regexec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_str(struct event_format *event,
		    struct filter_arg *arg, struct pevent_record *record)
{
	const char *val;

	if (arg->str.field == &comm)
		val = get_comm(event, record);
	else
		val = get_field_str(arg, record);

	switch (arg->str.type) {
	case FILTER_CMP_MATCH:
		return strcmp(val, arg->str.val) == 0;

	case FILTER_CMP_NOT_MATCH:
		return strcmp(val, arg->str.val) != 0;

	case FILTER_CMP_REGEX:
		/* Returns zero on match */
		return !regexec(&arg->str.reg, val, 0, NULL, 0);

	case FILTER_CMP_NOT_REGEX:
		return regexec(&arg->str.reg, val, 0, NULL, 0);

	default:
		/* ?? */
		return 0;
	}
}