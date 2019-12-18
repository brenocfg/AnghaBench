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
struct utrace_engine {int dummy; } ;
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UTRACE_ATTACH_MATCH_OPS ; 
 int /*<<< orphan*/  ptrace_utrace_ops ; 
 struct utrace_engine* utrace_attach_task (struct task_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct utrace_engine *ptrace_lookup_engine(struct task_struct *tracee)
{
	return utrace_attach_task(tracee, UTRACE_ATTACH_MATCH_OPS,
					&ptrace_utrace_ops, NULL);
}