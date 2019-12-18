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
struct perf_event_attr {int config; int /*<<< orphan*/  type; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_NAME_LEN ; 
 int /*<<< orphan*/  PERF_COUNT_HW_CACHE_MAX ; 
 int /*<<< orphan*/  PERF_COUNT_HW_CACHE_OP_MAX ; 
 int PERF_COUNT_HW_CACHE_OP_READ ; 
 int PERF_COUNT_HW_CACHE_RESULT_ACCESS ; 
 int /*<<< orphan*/  PERF_COUNT_HW_CACHE_RESULT_MAX ; 
 int /*<<< orphan*/  PERF_TYPE_HW_CACHE ; 
 int add_event (struct list_head**,int*,struct perf_event_attr*,char*) ; 
 int /*<<< orphan*/  memset (struct perf_event_attr*,int /*<<< orphan*/ ,int) ; 
 int parse_aliases (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_evsel__hw_cache ; 
 int /*<<< orphan*/  perf_evsel__hw_cache_op ; 
 int /*<<< orphan*/  perf_evsel__hw_cache_result ; 
 int /*<<< orphan*/  perf_evsel__is_cache_op_valid (int,int) ; 
 int snprintf (char*,int,char*,char*) ; 

int parse_events_add_cache(struct list_head **list, int *idx,
			   char *type, char *op_result1, char *op_result2)
{
	struct perf_event_attr attr;
	char name[MAX_NAME_LEN];
	int cache_type = -1, cache_op = -1, cache_result = -1;
	char *op_result[2] = { op_result1, op_result2 };
	int i, n;

	/*
	 * No fallback - if we cannot get a clear cache type
	 * then bail out:
	 */
	cache_type = parse_aliases(type, perf_evsel__hw_cache,
				   PERF_COUNT_HW_CACHE_MAX);
	if (cache_type == -1)
		return -EINVAL;

	n = snprintf(name, MAX_NAME_LEN, "%s", type);

	for (i = 0; (i < 2) && (op_result[i]); i++) {
		char *str = op_result[i];

		n += snprintf(name + n, MAX_NAME_LEN - n, "-%s", str);

		if (cache_op == -1) {
			cache_op = parse_aliases(str, perf_evsel__hw_cache_op,
						 PERF_COUNT_HW_CACHE_OP_MAX);
			if (cache_op >= 0) {
				if (!perf_evsel__is_cache_op_valid(cache_type, cache_op))
					return -EINVAL;
				continue;
			}
		}

		if (cache_result == -1) {
			cache_result = parse_aliases(str, perf_evsel__hw_cache_result,
						     PERF_COUNT_HW_CACHE_RESULT_MAX);
			if (cache_result >= 0)
				continue;
		}
	}

	/*
	 * Fall back to reads:
	 */
	if (cache_op == -1)
		cache_op = PERF_COUNT_HW_CACHE_OP_READ;

	/*
	 * Fall back to accesses:
	 */
	if (cache_result == -1)
		cache_result = PERF_COUNT_HW_CACHE_RESULT_ACCESS;

	memset(&attr, 0, sizeof(attr));
	attr.config = cache_type | (cache_op << 8) | (cache_result << 16);
	attr.type = PERF_TYPE_HW_CACHE;
	return add_event(list, idx, &attr, name);
}