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
 void __hists__collapse_resort (struct hists*,int) ; 

void hists__collapse_resort(struct hists *hists)
{
	return __hists__collapse_resort(hists, false);
}