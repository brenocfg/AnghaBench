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
struct TYPE_2__ {scalar_t__ type; scalar_t__ config; } ;
struct perf_evsel {TYPE_1__ attr; } ;

/* Variables and functions */

__attribute__((used)) static inline bool perf_evsel__match2(struct perf_evsel *e1,
				      struct perf_evsel *e2)
{
	return (e1->attr.type == e2->attr.type) &&
	       (e1->attr.config == e2->attr.config);
}