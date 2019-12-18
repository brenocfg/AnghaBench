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
struct hist_entry {int dummy; } ;
struct hist_browser {struct hist_entry* he_selection; } ;

/* Variables and functions */

__attribute__((used)) static struct hist_entry *hist_browser__selected_entry(struct hist_browser *browser)
{
	return browser->he_selection;
}