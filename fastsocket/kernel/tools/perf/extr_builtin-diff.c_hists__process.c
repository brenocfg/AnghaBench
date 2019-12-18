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
struct hists {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists__baseline_only (struct hists*) ; 
 int /*<<< orphan*/  hists__compute_resort (struct hists*) ; 
 int /*<<< orphan*/  hists__fprintf (struct hists*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hists__link (struct hists*,struct hists*) ; 
 int /*<<< orphan*/  hists__match (struct hists*,struct hists*) ; 
 int /*<<< orphan*/  hists__precompute (struct hists*) ; 
 scalar_t__ show_baseline_only ; 
 scalar_t__ sort_compute ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void hists__process(struct hists *old, struct hists *new)
{
	hists__match(new, old);

	if (show_baseline_only)
		hists__baseline_only(new);
	else
		hists__link(new, old);

	if (sort_compute) {
		hists__precompute(new);
		hists__compute_resort(new);
	}

	hists__fprintf(new, true, 0, 0, stdout);
}