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
typedef  int /*<<< orphan*/  u32 ;
struct smk_audit_info {int dummy; } ;
struct TYPE_4__ {TYPE_1__* cred; } ;
struct TYPE_3__ {int /*<<< orphan*/ * security; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_MAC_OVERRIDE ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 char* current_security () ; 
 int /*<<< orphan*/  smack_log (char*,char*,int /*<<< orphan*/ ,int,struct smk_audit_info*) ; 
 int /*<<< orphan*/ * smack_onlycap ; 
 int smk_access (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int smk_curacc(char *obj_label, u32 mode, struct smk_audit_info *a)
{
	int rc;
	char *sp = current_security();

	rc = smk_access(sp, obj_label, mode, NULL);
	if (rc == 0)
		goto out_audit;

	/*
	 * Return if a specific label has been designated as the
	 * only one that gets privilege and current does not
	 * have that label.
	 */
	if (smack_onlycap != NULL && smack_onlycap != current->cred->security)
		goto out_audit;

	if (capable(CAP_MAC_OVERRIDE))
		return 0;

out_audit:
#ifdef CONFIG_AUDIT
	if (a)
		smack_log(sp, obj_label, mode, rc, a);
#endif
	return rc;
}