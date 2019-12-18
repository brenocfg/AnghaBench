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
struct dlm_ctxt {int /*<<< orphan*/ * dlm_worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_destroy_dlm_worker(struct dlm_ctxt *dlm)
{
	if (dlm->dlm_worker) {
		flush_workqueue(dlm->dlm_worker);
		destroy_workqueue(dlm->dlm_worker);
		dlm->dlm_worker = NULL;
	}
}