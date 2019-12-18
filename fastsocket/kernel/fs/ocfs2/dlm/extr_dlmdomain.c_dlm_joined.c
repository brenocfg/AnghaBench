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
struct dlm_ctxt {scalar_t__ dlm_state; } ;

/* Variables and functions */
 scalar_t__ DLM_CTXT_JOINED ; 
 int /*<<< orphan*/  dlm_domain_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int dlm_joined(struct dlm_ctxt *dlm)
{
	int ret = 0;

	spin_lock(&dlm_domain_lock);

	if (dlm->dlm_state == DLM_CTXT_JOINED)
		ret = 1;

	spin_unlock(&dlm_domain_lock);

	return ret;
}