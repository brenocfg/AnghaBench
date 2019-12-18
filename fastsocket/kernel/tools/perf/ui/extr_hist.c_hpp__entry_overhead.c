#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct perf_hpp {int /*<<< orphan*/  size; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {double total_period; } ;
struct hists {TYPE_2__ stats; } ;
struct TYPE_4__ {double period; } ;
struct hist_entry {TYPE_1__ stat; struct hists* hists; } ;
struct TYPE_6__ {scalar_t__ field_sep; } ;

/* Variables and functions */
 int scnprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,double) ; 
 TYPE_3__ symbol_conf ; 

__attribute__((used)) static int hpp__entry_overhead(struct perf_hpp *hpp, struct hist_entry *he)
{
	struct hists *hists = he->hists;
	double percent = 100.0 * he->stat.period / hists->stats.total_period;
	const char *fmt = symbol_conf.field_sep ? "%.2f" : " %6.2f%%";

	return scnprintf(hpp->buf, hpp->size, fmt, percent);
}