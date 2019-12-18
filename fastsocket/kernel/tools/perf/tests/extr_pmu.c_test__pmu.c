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
struct perf_event_attr {int config; int config1; int config2; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  formats ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 int perf_pmu__config_terms (int /*<<< orphan*/ *,struct perf_event_attr*,struct list_head*) ; 
 int perf_pmu__format_parse (char*,int /*<<< orphan*/ *) ; 
 char* test_format_dir_get () ; 
 int /*<<< orphan*/  test_format_dir_put (char*) ; 
 struct list_head* test_terms_list () ; 

int test__pmu(void)
{
	char *format = test_format_dir_get();
	LIST_HEAD(formats);
	struct list_head *terms = test_terms_list();
	int ret;

	if (!format)
		return -EINVAL;

	do {
		struct perf_event_attr attr;

		memset(&attr, 0, sizeof(attr));

		ret = perf_pmu__format_parse(format, &formats);
		if (ret)
			break;

		ret = perf_pmu__config_terms(&formats, &attr, terms);
		if (ret)
			break;

		ret = -EINVAL;

		if (attr.config  != 0xc00000000002a823)
			break;
		if (attr.config1 != 0x8000400000000145)
			break;
		if (attr.config2 != 0x0400000020041d07)
			break;

		ret = 0;
	} while (0);

	test_format_dir_put(format);
	return ret;
}