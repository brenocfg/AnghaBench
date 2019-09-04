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
typedef  scalar_t__ thread_t ;
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  xstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVX512 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* current_task () ; 
 scalar_t__ current_thread () ; 
 int /*<<< orphan*/  fpu_savearea_promote_avx512 (scalar_t__) ; 
 int /*<<< orphan*/  ml_fpu_avx512_enabled () ; 

boolean_t
fpu_thread_promote_avx512(thread_t thread)
{
	task_t		task = current_task();

	if (thread != current_thread())
		return FALSE;
	if (!ml_fpu_avx512_enabled())
		return FALSE;

	fpu_savearea_promote_avx512(thread);

	/* Racy but the task's xstate is only a hint */
	task->xstate = AVX512;

	return TRUE;
}