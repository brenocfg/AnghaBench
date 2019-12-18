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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {int dummy; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_state; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t
lpfc_device_rm_logo_issue(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			  void *arg, uint32_t evt)
{
	/*
	 * Take no action.  If a LOGO is outstanding, then possibly DevLoss has
	 * timed out and is calling for Device Remove.  In this case, the LOGO
	 * must be allowed to complete in state LOGO_ISSUE so that the rpi
	 * and other NLP flags are correctly cleaned up.
	 */
	return ndlp->nlp_state;
}