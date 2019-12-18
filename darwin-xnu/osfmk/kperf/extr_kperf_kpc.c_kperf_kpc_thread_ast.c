#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_5__ {scalar_t__ kperf_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  kpc_thread_ast_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  kperf_thread_ast_handler (TYPE_1__*) ; 

void
kperf_kpc_thread_ast(thread_t thread)
{
	kpc_thread_ast_handler(thread);
	kperf_thread_ast_handler(thread);

	thread->kperf_flags = 0;
}