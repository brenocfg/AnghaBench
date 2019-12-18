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
struct perf_hpp {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct hist_entry {int dummy; } ;

/* Variables and functions */
 double baseline_percent (struct hist_entry*) ; 
 scalar_t__ hist_entry__has_pairs (struct hist_entry*) ; 
 int percent_color_snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,double) ; 
 int scnprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int hpp__color_baseline(struct perf_hpp *hpp, struct hist_entry *he)
{
	double percent = baseline_percent(he);

	if (hist_entry__has_pairs(he))
		return percent_color_snprintf(hpp->buf, hpp->size, " %6.2f%%", percent);
	else
		return scnprintf(hpp->buf, hpp->size, "        ");
}