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
typedef  scalar_t__ timeout_fcn_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  thread_call_func_cancel (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

void
bsd_untimeout(
	timeout_fcn_t		fcn,
	void			*param)
{
	thread_call_func_cancel((thread_call_func_t)fcn, param, FALSE);
}