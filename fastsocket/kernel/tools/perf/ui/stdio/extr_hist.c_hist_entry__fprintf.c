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
struct perf_hpp {char* buf; size_t size; } ;
struct hists {int dummy; } ;
struct hist_entry {int dummy; } ;
typedef  int /*<<< orphan*/  bf ;
struct TYPE_2__ {scalar_t__ use_callchain; int /*<<< orphan*/  field_sep; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ hist_entry__callchain_fprintf (struct hist_entry*,struct hists*,int /*<<< orphan*/ *) ; 
 int hist_entry__period_snprintf (struct perf_hpp*,struct hist_entry*,int) ; 
 int /*<<< orphan*/  hist_entry__sort_snprintf (struct hist_entry*,char*,size_t,struct hists*) ; 
 TYPE_1__ symbol_conf ; 

__attribute__((used)) static int hist_entry__fprintf(struct hist_entry *he, size_t size,
			       struct hists *hists, FILE *fp)
{
	char bf[512];
	int ret;
	struct perf_hpp hpp = {
		.buf		= bf,
		.size		= size,
	};
	bool color = !symbol_conf.field_sep;

	if (size == 0 || size > sizeof(bf))
		size = hpp.size = sizeof(bf);

	ret = hist_entry__period_snprintf(&hpp, he, color);
	hist_entry__sort_snprintf(he, bf + ret, size - ret, hists);

	ret = fprintf(fp, "%s\n", bf);

	if (symbol_conf.use_callchain)
		ret += hist_entry__callchain_fprintf(he, hists, fp);

	return ret;
}