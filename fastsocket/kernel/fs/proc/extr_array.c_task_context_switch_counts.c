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
struct task_struct {int /*<<< orphan*/  nivcsw; int /*<<< orphan*/  nvcsw; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void task_context_switch_counts(struct seq_file *m,
						struct task_struct *p)
{
	seq_printf(m,	"voluntary_ctxt_switches:\t%lu\n"
			"nonvoluntary_ctxt_switches:\t%lu\n",
			p->nvcsw,
			p->nivcsw);
}