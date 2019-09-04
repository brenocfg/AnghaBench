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
typedef  int /*<<< orphan*/  thread_t ;
struct uthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_thread () ; 
 scalar_t__ get_bsdthread_info (int /*<<< orphan*/ ) ; 

struct uthread *
current_uthread()
{
	thread_t th = current_thread();

	return((struct uthread *)get_bsdthread_info(th));
}