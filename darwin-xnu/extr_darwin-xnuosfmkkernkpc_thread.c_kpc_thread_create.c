#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  kpc_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kpc_counterbuf_alloc () ; 
 int /*<<< orphan*/  kpc_threads_counting ; 

void
kpc_thread_create(thread_t thread)
{
	/* nothing to do if we're not counting */
	if(!kpc_threads_counting)
		return;

	/* give the new thread a counterbuf */
	thread->kpc_buf = kpc_counterbuf_alloc();
}