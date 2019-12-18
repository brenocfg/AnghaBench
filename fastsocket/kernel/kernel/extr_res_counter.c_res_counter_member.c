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
struct res_counter {unsigned long long usage; unsigned long long max_usage; unsigned long long limit; unsigned long long failcnt; unsigned long long soft_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  RES_FAILCNT 132 
#define  RES_LIMIT 131 
#define  RES_MAX_USAGE 130 
#define  RES_SOFT_LIMIT 129 
#define  RES_USAGE 128 

__attribute__((used)) static inline unsigned long long *
res_counter_member(struct res_counter *counter, int member)
{
	switch (member) {
	case RES_USAGE:
		return &counter->usage;
	case RES_MAX_USAGE:
		return &counter->max_usage;
	case RES_LIMIT:
		return &counter->limit;
	case RES_FAILCNT:
		return &counter->failcnt;
	case RES_SOFT_LIMIT:
		return &counter->soft_limit;
	};

	BUG();
	return NULL;
}