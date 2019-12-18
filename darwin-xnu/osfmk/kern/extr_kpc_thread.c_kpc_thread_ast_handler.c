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
struct TYPE_3__ {int kperf_flags; int /*<<< orphan*/  kpc_buf; } ;

/* Variables and functions */
 int T_KPC_ALLOC ; 
 int /*<<< orphan*/  kpc_counterbuf_alloc () ; 

void
kpc_thread_ast_handler( thread_t thread )
{
	/* see if we want an alloc */
	if( thread->kperf_flags & T_KPC_ALLOC )
		thread->kpc_buf = kpc_counterbuf_alloc();
}