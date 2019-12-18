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
struct perf_hpp {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct hist_entry {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ field_sep; } ;

/* Variables and functions */
 int /*<<< orphan*/  perf_diff__formula (char*,int,struct hist_entry*) ; 
 int scnprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int hpp__entry_formula(struct perf_hpp *hpp, struct hist_entry *he)
{
	const char *fmt = symbol_conf.field_sep ? "%s" : "%-70s";
	char buf[96] = " ";

	perf_diff__formula(buf, sizeof(buf), he);
	return scnprintf(hpp->buf, hpp->size, fmt, buf);
}