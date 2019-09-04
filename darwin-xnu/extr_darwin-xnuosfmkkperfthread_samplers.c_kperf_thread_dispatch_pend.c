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
struct kperf_context {int /*<<< orphan*/  cur_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  T_KPERF_AST_DISPATCH ; 
 int kperf_ast_pend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
kperf_thread_dispatch_pend(struct kperf_context *context)
{
	return kperf_ast_pend(context->cur_thread, T_KPERF_AST_DISPATCH);
}