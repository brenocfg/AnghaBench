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
 int /*<<< orphan*/  lpfc_issue_els_logo (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
lpfc_rcv_els_unused_node(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
			 void *arg, uint32_t evt)
{
	lpfc_issue_els_logo(vport, ndlp, 0);
	return ndlp->nlp_state;
}