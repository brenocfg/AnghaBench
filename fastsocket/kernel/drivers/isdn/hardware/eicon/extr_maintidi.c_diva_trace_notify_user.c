#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  user_context; int /*<<< orphan*/  (* notify_proc ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * lines; int /*<<< orphan*/  Adapter; int /*<<< orphan*/  instance; TYPE_1__ user_proc_table; } ;
typedef  TYPE_2__ diva_strace_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void diva_trace_notify_user (diva_strace_context_t* pLib,
														 int Channel,
														 int notify_subject) {
	if (pLib->user_proc_table.notify_proc) {
		(*(pLib->user_proc_table.notify_proc))(pLib->user_proc_table.user_context,
																					 &pLib->instance,
																					 pLib->Adapter,
																					 &pLib->lines[Channel],
																					 notify_subject);
	}
}