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
struct perf_sample {int dummy; } ;
struct perf_evsel {int dummy; } ;
struct event_key {int /*<<< orphan*/  key; scalar_t__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_evsel__intval (struct perf_evsel*,struct perf_sample*,char*) ; 

__attribute__((used)) static void exit_event_get_key(struct perf_evsel *evsel,
			       struct perf_sample *sample,
			       struct event_key *key)
{
	key->info = 0;
	key->key = perf_evsel__intval(evsel, sample, "exit_reason");
}