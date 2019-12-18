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
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  wf_client_list ; 

__attribute__((used)) static inline void wf_notify(int event, void *param)
{
	blocking_notifier_call_chain(&wf_client_list, event, param);
}