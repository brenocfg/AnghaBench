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

/* Variables and functions */
 int /*<<< orphan*/  EVENT_ITEM ; 
 int /*<<< orphan*/  EVENT_OP ; 
 int /*<<< orphan*/  free_token (char*) ; 
 scalar_t__ read_expect_type (int /*<<< orphan*/ ,char**) ; 
 scalar_t__ read_expected (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *event_read_name(void)
{
	char *token;

	if (read_expected(EVENT_ITEM, "name") < 0)
		return NULL;

	if (read_expected(EVENT_OP, ":") < 0)
		return NULL;

	if (read_expect_type(EVENT_ITEM, &token) < 0)
		goto fail;

	return token;

 fail:
	free_token(token);
	return NULL;
}