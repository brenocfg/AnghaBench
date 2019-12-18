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
struct smack_cipso {char* smk_catset; int /*<<< orphan*/  smk_level; } ;
struct TYPE_4__ {int /*<<< orphan*/  lvl; } ;
struct TYPE_3__ {TYPE_2__ mls; } ;
struct netlbl_lsm_secattr {char* domain; int flags; TYPE_1__ attr; } ;

/* Variables and functions */
 int NETLBL_SECATTR_DOMAIN ; 
 int NETLBL_SECATTR_MLS_LVL ; 
 int /*<<< orphan*/  smack_cipso_direct ; 
 int /*<<< orphan*/  smack_set_catset (char*,struct netlbl_lsm_secattr*) ; 
 int smack_to_cipso (char*,struct smack_cipso*) ; 

__attribute__((used)) static void smack_to_secattr(char *smack, struct netlbl_lsm_secattr *nlsp)
{
	struct smack_cipso cipso;
	int rc;

	nlsp->domain = smack;
	nlsp->flags = NETLBL_SECATTR_DOMAIN | NETLBL_SECATTR_MLS_LVL;

	rc = smack_to_cipso(smack, &cipso);
	if (rc == 0) {
		nlsp->attr.mls.lvl = cipso.smk_level;
		smack_set_catset(cipso.smk_catset, nlsp);
	} else {
		nlsp->attr.mls.lvl = smack_cipso_direct;
		smack_set_catset(smack, nlsp);
	}
}