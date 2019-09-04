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
typedef  TYPE_1__* task_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int t_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int TF_GPU_DENIED ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t task_is_gpu_denied(task_t task)
{
	/* We don't need the lock to read this flag */
	return (task->t_flags & TF_GPU_DENIED) ? TRUE : FALSE;
}