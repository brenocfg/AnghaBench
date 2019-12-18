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
struct lpfc_hba {int /*<<< orphan*/  worker_thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_unset_driver_resource_phase2(struct lpfc_hba *phba)
{
	/* Stop kernel worker thread */
	kthread_stop(phba->worker_thread);
}