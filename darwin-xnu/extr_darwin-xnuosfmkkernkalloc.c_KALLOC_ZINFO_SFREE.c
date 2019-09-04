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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_5__ {int /*<<< orphan*/  tkm_shared; } ;
struct TYPE_4__ {int /*<<< orphan*/  t_ledger; } ;

/* Variables and functions */
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  ledger_credit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ task_ledgers ; 

__attribute__((used)) static void
KALLOC_ZINFO_SFREE(vm_size_t bytes)
{
	thread_t thr = current_thread();
	ledger_credit(thr->t_ledger, task_ledgers.tkm_shared, bytes);
}