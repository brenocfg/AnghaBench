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
typedef  int /*<<< orphan*/  thread_t ;
struct stackshot_thread_waitinfo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pthread_find_owner ) (int /*<<< orphan*/ ,struct stackshot_thread_waitinfo*) ;} ;

/* Variables and functions */
 TYPE_1__* pthread_functions ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct stackshot_thread_waitinfo*) ; 

void
kdp_pthread_find_owner(thread_t thread, struct stackshot_thread_waitinfo *waitinfo)
{
	if (pthread_functions->pthread_find_owner)
		pthread_functions->pthread_find_owner(thread, waitinfo);
}