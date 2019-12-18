#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct perf_evsel {struct cpu_map* cpus; } ;
struct cpu_map {int dummy; } ;
struct TYPE_4__ {struct cpu_map* cpus; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpu_list; } ;

/* Variables and functions */
 TYPE_2__* evsel_list ; 
 TYPE_1__ target ; 

__attribute__((used)) static inline struct cpu_map *perf_evsel__cpus(struct perf_evsel *evsel)
{
	return (evsel->cpus && !target.cpu_list) ? evsel->cpus : evsel_list->cpus;
}