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
typedef  int /*<<< orphan*/  interface_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  dlil_detach_filter (int /*<<< orphan*/ ) ; 

void
iflt_detach(
	interface_filter_t filter_ref)
{
	dlil_detach_filter(filter_ref);
}