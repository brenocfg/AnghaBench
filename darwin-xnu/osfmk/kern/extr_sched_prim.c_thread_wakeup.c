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
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_AWAKENED ; 
 int /*<<< orphan*/  thread_wakeup_with_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
thread_wakeup(
       event_t         x)
{
       thread_wakeup_with_result(x, THREAD_AWAKENED);
}