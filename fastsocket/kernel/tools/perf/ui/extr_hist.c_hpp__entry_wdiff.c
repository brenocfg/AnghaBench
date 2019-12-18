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
struct perf_hpp {char* buf; int size; } ;
struct TYPE_3__ {scalar_t__ wdiff; scalar_t__ computed; } ;
struct hist_entry {TYPE_1__ diff; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {scalar_t__ field_sep; } ;

/* Variables and functions */
 scalar_t__ perf_diff__compute_wdiff (struct hist_entry*) ; 
 int scnprintf (char*,int,char const*,char*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static int hpp__entry_wdiff(struct perf_hpp *hpp, struct hist_entry *he)
{
	const char *fmt = symbol_conf.field_sep ? "%s" : "%14s";
	char buf[32] = " ";
	s64 wdiff;

	if (he->diff.computed)
		wdiff = he->diff.wdiff;
	else
		wdiff = perf_diff__compute_wdiff(he);

	if (wdiff != 0)
		scnprintf(buf, sizeof(buf), "%14ld", wdiff);

	return scnprintf(hpp->buf, hpp->size, fmt, buf);
}