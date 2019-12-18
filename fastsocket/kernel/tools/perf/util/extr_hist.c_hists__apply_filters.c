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
struct hist_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hists__filter_entry_by_dso (struct hists*,struct hist_entry*) ; 
 int /*<<< orphan*/  hists__filter_entry_by_symbol (struct hists*,struct hist_entry*) ; 
 int /*<<< orphan*/  hists__filter_entry_by_thread (struct hists*,struct hist_entry*) ; 

__attribute__((used)) static void hists__apply_filters(struct hists *hists, struct hist_entry *he)
{
	hists__filter_entry_by_dso(hists, he);
	hists__filter_entry_by_thread(hists, he);
	hists__filter_entry_by_symbol(hists, he);
}