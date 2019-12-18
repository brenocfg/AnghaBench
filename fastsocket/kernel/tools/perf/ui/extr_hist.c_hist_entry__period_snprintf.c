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
struct perf_hpp {char* buf; int /*<<< orphan*/  size; } ;
struct hist_entry {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int (* color ) (struct perf_hpp*,struct hist_entry*) ;int (* entry ) (struct perf_hpp*,struct hist_entry*) ;int /*<<< orphan*/  cond; } ;
struct TYPE_3__ {char* field_sep; scalar_t__ exclude_other; } ;

/* Variables and functions */
 int PERF_HPP__MAX_INDEX ; 
 int /*<<< orphan*/  advance_hpp (struct perf_hpp*,int) ; 
 TYPE_2__* perf_hpp__format ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int stub1 (struct perf_hpp*,struct hist_entry*) ; 
 int stub2 (struct perf_hpp*,struct hist_entry*) ; 
 TYPE_1__ symbol_conf ; 

int hist_entry__period_snprintf(struct perf_hpp *hpp, struct hist_entry *he,
				bool color)
{
	const char *sep = symbol_conf.field_sep;
	char *start = hpp->buf;
	int i, ret;
	bool first = true;

	if (symbol_conf.exclude_other && !he->parent)
		return 0;

	for (i = 0; i < PERF_HPP__MAX_INDEX; i++) {
		if (!perf_hpp__format[i].cond)
			continue;

		/*
		 * If there's no field_sep, we still need
		 * to display initial '  '.
		 */
		if (!sep || !first) {
			ret = scnprintf(hpp->buf, hpp->size, "%s", sep ?: "  ");
			advance_hpp(hpp, ret);
		} else
			first = false;

		if (color && perf_hpp__format[i].color)
			ret = perf_hpp__format[i].color(hpp, he);
		else
			ret = perf_hpp__format[i].entry(hpp, he);

		advance_hpp(hpp, ret);
	}

	return hpp->buf - start;
}