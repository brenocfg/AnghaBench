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
struct hist_entry {long position; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {scalar_t__ field_sep; } ;

/* Variables and functions */
 struct hist_entry* hist_entry__next_pair (struct hist_entry*) ; 
 int scnprintf (char*,int,char const*,...) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int hpp__entry_displ(struct perf_hpp *hpp,
			    struct hist_entry *he)
{
	struct hist_entry *pair = hist_entry__next_pair(he);
	long displacement = pair ? pair->position - he->position : 0;
	const char *fmt = symbol_conf.field_sep ? "%s" : "%6.6s";
	char buf[32] = " ";

	if (displacement)
		scnprintf(buf, sizeof(buf), "%+4ld", displacement);

	return scnprintf(hpp->buf, hpp->size, fmt, buf);
}