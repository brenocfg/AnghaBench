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
struct TYPE_2__ {char* format; int /*<<< orphan*/ * args; } ;
struct event_format {TYPE_1__ print_fmt; } ;
typedef  enum event_type { ____Placeholder_event_type } event_type ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_DELIM ; 
 int EVENT_DQUOTE ; 
 int /*<<< orphan*/  EVENT_ITEM ; 
 int EVENT_NONE ; 
 int /*<<< orphan*/  EVENT_OP ; 
 scalar_t__ asprintf (char**,char*,char*,char*) ; 
 int event_read_print_args (struct event_format*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  free_token (char*) ; 
 scalar_t__ read_expect_type (int,char**) ; 
 scalar_t__ read_expected (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_expected_item (int /*<<< orphan*/ ,char*) ; 
 int read_token_item (char**) ; 
 scalar_t__ test_type_token (int,char*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int event_read_print(struct event_format *event)
{
	enum event_type type;
	char *token;
	int ret;

	if (read_expected_item(EVENT_ITEM, "print") < 0)
		return -1;

	if (read_expected(EVENT_ITEM, "fmt") < 0)
		return -1;

	if (read_expected(EVENT_OP, ":") < 0)
		return -1;

	if (read_expect_type(EVENT_DQUOTE, &token) < 0)
		goto fail;

 concat:
	event->print_fmt.format = token;
	event->print_fmt.args = NULL;

	/* ok to have no arg */
	type = read_token_item(&token);

	if (type == EVENT_NONE)
		return 0;

	/* Handle concatenation of print lines */
	if (type == EVENT_DQUOTE) {
		char *cat;

		if (asprintf(&cat, "%s%s", event->print_fmt.format, token) < 0)
			goto fail;
		free_token(token);
		free_token(event->print_fmt.format);
		event->print_fmt.format = NULL;
		token = cat;
		goto concat;
	}
			     
	if (test_type_token(type, token, EVENT_DELIM, ","))
		goto fail;

	free_token(token);

	ret = event_read_print_args(event, &event->print_fmt.args);
	if (ret < 0)
		return -1;

	return ret;

 fail:
	free_token(token);
	return -1;
}