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
 int /*<<< orphan*/  TIF_USEDFPU ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_used_math () ; 
 int /*<<< orphan*/  current ; 

void flush_thread(void)
{
	clear_used_math();
	clear_tsk_thread_flag(current, TIF_USEDFPU);
}