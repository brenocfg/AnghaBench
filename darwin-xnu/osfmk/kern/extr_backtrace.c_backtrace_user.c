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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int backtrace_thread_user (int /*<<< orphan*/ ,uintptr_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  current_thread () ; 

int
backtrace_user(uintptr_t *bt, uint32_t max_frames, uint32_t *frames_out,
	bool *user_64_out)
{
	return backtrace_thread_user(current_thread(), bt, max_frames, frames_out,
		user_64_out);
}