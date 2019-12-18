#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lpfc_vport {int /*<<< orphan*/  fc_fdmitmo; } ;
struct lpfc_nodelist {int dummy; } ;
struct TYPE_2__ {char* nodename; } ;

/* Variables and functions */
 int /*<<< orphan*/  FDMI_DID ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  SLI_MGMT_DHBA ; 
 TYPE_1__* init_utsname () ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  lpfc_fdmi_cmd (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 

void
lpfc_fdmi_timeout_handler(struct lpfc_vport *vport)
{
	struct lpfc_nodelist *ndlp;

	ndlp = lpfc_findnode_did(vport, FDMI_DID);
	if (ndlp && NLP_CHK_NODE_ACT(ndlp)) {
		if (init_utsname()->nodename[0] != '\0')
			lpfc_fdmi_cmd(vport, ndlp, SLI_MGMT_DHBA);
		else
			mod_timer(&vport->fc_fdmitmo, jiffies +
				  msecs_to_jiffies(1000 * 60));
	}
	return;
}