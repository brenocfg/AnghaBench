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
 int blocking_notifier_call_chain (int /*<<< orphan*/ *,unsigned long,void*) ; 
 int /*<<< orphan*/  fb_notifier_list ; 

int fb_notifier_call_chain(unsigned long val, void *v)
{
	return blocking_notifier_call_chain(&fb_notifier_list, val, v);
}