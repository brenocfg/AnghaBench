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
 void __hists__decay_entries (struct hists*,int,int,int) ; 

void hists__decay_entries_threaded(struct hists *hists,
				   bool zap_user, bool zap_kernel)
{
	return __hists__decay_entries(hists, zap_user, zap_kernel, true);
}