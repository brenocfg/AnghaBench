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
typedef  size_t u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * nr_events; } ;
struct hists {TYPE_1__ stats; } ;

/* Variables and functions */

void hists__inc_nr_events(struct hists *hists, u32 type)
{
	++hists->stats.nr_events[0];
	++hists->stats.nr_events[type];
}