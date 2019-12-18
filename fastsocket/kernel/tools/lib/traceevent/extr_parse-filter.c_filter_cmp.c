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
struct filter_type {scalar_t__ event_id; } ;

/* Variables and functions */

__attribute__((used)) static int filter_cmp(const void *a, const void *b)
{
	const struct filter_type *ea = a;
	const struct filter_type *eb = b;

	if (ea->event_id < eb->event_id)
		return -1;

	if (ea->event_id > eb->event_id)
		return 1;

	return 0;
}