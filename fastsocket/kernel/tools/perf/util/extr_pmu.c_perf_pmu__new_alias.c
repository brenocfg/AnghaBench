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
struct perf_pmu__alias {int /*<<< orphan*/  list; int /*<<< orphan*/  name; int /*<<< orphan*/  terms; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct perf_pmu__alias*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct perf_pmu__alias* malloc (int) ; 
 int parse_events_terms (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strdup (char*) ; 

__attribute__((used)) static int perf_pmu__new_alias(struct list_head *list, char *name, FILE *file)
{
	struct perf_pmu__alias *alias;
	char buf[256];
	int ret;

	ret = fread(buf, 1, sizeof(buf), file);
	if (ret == 0)
		return -EINVAL;
	buf[ret] = 0;

	alias = malloc(sizeof(*alias));
	if (!alias)
		return -ENOMEM;

	INIT_LIST_HEAD(&alias->terms);
	ret = parse_events_terms(&alias->terms, buf);
	if (ret) {
		free(alias);
		return ret;
	}

	alias->name = strdup(name);
	list_add_tail(&alias->list, list);
	return 0;
}