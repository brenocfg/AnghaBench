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
struct TYPE_2__ {scalar_t__ ts_jiffies; } ;

/* Variables and functions */
 TYPE_1__* xpc_rsvd_page ; 

void
xpc_teardown_rsvd_page(void)
{
	/* a zero timestamp indicates our rsvd page is not initialized */
	xpc_rsvd_page->ts_jiffies = 0;
}