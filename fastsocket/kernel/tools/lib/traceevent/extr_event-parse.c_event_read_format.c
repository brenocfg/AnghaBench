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
struct TYPE_2__ {int nr_common; int nr_fields; int /*<<< orphan*/  fields; int /*<<< orphan*/  common_fields; } ;
struct event_format {TYPE_1__ format; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ITEM ; 
 int /*<<< orphan*/  EVENT_NEWLINE ; 
 int /*<<< orphan*/  EVENT_OP ; 
 int event_read_fields (struct event_format*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_token (char*) ; 
 scalar_t__ read_expect_type (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ read_expected (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ read_expected_item (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int event_read_format(struct event_format *event)
{
	char *token;
	int ret;

	if (read_expected_item(EVENT_ITEM, "format") < 0)
		return -1;

	if (read_expected(EVENT_OP, ":") < 0)
		return -1;

	if (read_expect_type(EVENT_NEWLINE, &token))
		goto fail;
	free_token(token);

	ret = event_read_fields(event, &event->format.common_fields);
	if (ret < 0)
		return ret;
	event->format.nr_common = ret;

	ret = event_read_fields(event, &event->format.fields);
	if (ret < 0)
		return ret;
	event->format.nr_fields = ret;

	return 0;

 fail:
	free_token(token);
	return -1;
}