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
struct perf_pmu__format {int value; int /*<<< orphan*/  list; int /*<<< orphan*/  bits; int /*<<< orphan*/  name; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 struct perf_pmu__format* zalloc (int) ; 

int perf_pmu__new_format(struct list_head *list, char *name,
			 int config, unsigned long *bits)
{
	struct perf_pmu__format *format;

	format = zalloc(sizeof(*format));
	if (!format)
		return -ENOMEM;

	format->name = strdup(name);
	format->value = config;
	memcpy(format->bits, bits, sizeof(format->bits));

	list_add_tail(&format->list, list);
	return 0;
}