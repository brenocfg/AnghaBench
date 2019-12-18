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

/* Variables and functions */
 int /*<<< orphan*/  gtk_helpline_fns ; 
 int /*<<< orphan*/ * helpline_fns ; 

void perf_gtk__init_helpline(void)
{
	helpline_fns = &gtk_helpline_fns;
}