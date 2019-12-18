#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uml_tls_struct {scalar_t__ flushed; int /*<<< orphan*/  present; } ;
struct TYPE_3__ {struct uml_tls_struct* tls_array; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;
struct task_struct {TYPE_2__ thread; } ;

/* Variables and functions */
 int GDT_ENTRY_TLS_MAX ; 
 int GDT_ENTRY_TLS_MIN ; 

void clear_flushed_tls(struct task_struct *task)
{
	int i;

	for (i = GDT_ENTRY_TLS_MIN; i < GDT_ENTRY_TLS_MAX; i++) {
		struct uml_tls_struct* curr =
			&task->thread.arch.tls_array[i - GDT_ENTRY_TLS_MIN];

		/*
		 * Still correct to do this, if it wasn't present on the host it
		 * will remain as flushed as it was.
		 */
		if (!curr->present)
			continue;

		curr->flushed = 0;
	}
}