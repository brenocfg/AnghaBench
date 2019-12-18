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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLANK () ; 
 int /*<<< orphan*/  COMMENT (char*) ; 
 int /*<<< orphan*/  DEFINE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OFFSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TASK_FLAGS ; 
 int /*<<< orphan*/  TASK_MM ; 
 int /*<<< orphan*/  TASK_PID ; 
 int /*<<< orphan*/  TASK_STATE ; 
 int /*<<< orphan*/  TASK_STRUCT_SIZE ; 
 int /*<<< orphan*/  TASK_THREAD_INFO ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  mm ; 
 int /*<<< orphan*/  pid ; 
 int /*<<< orphan*/  stack ; 
 int /*<<< orphan*/  state ; 
 int /*<<< orphan*/  task_struct ; 

void output_task_defines(void)
{
	COMMENT("SCORE task_struct offsets.");
	OFFSET(TASK_STATE, task_struct, state);
	OFFSET(TASK_THREAD_INFO, task_struct, stack);
	OFFSET(TASK_FLAGS, task_struct, flags);
	OFFSET(TASK_MM, task_struct, mm);
	OFFSET(TASK_PID, task_struct, pid);
	DEFINE(TASK_STRUCT_SIZE, sizeof(struct task_struct));
	BLANK();
}