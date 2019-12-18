#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct ip6_fw_chain* le_next; } ;
struct ip6_fw_chain {TYPE_1__* rule; TYPE_2__ chain; } ;
struct ip6_fw {scalar_t__ fw_number; } ;
struct TYPE_6__ {struct ip6_fw_chain* lh_first; } ;
struct TYPE_4__ {scalar_t__ fw_number; scalar_t__ timestamp; scalar_t__ fw_pcnt; scalar_t__ fw_bcnt; } ;

/* Variables and functions */
 int LOG_AUTHPRIV ; 
 int LOG_NOTICE ; 
 scalar_t__ fw6_verbose ; 
 TYPE_3__ ip6_fw_chain ; 
 int /*<<< orphan*/  log (int,char*,...) ; 

__attribute__((used)) static int
zero_entry6(struct ip6_fw *frwl)
{
	struct ip6_fw_chain *fcp;

	/*
	 *	It's possible to insert multiple chain entries with the
	 *	same number, so we don't stop after finding the first
	 *	match if zeroing a specific entry.
	 */
	for (fcp = ip6_fw_chain.lh_first; fcp; fcp = fcp->chain.le_next)
		if (!frwl || frwl->fw_number == 0 || frwl->fw_number == fcp->rule->fw_number) {
			fcp->rule->fw_bcnt = fcp->rule->fw_pcnt = 0;
			fcp->rule->timestamp = 0;
		}

	if (fw6_verbose) {
		if (frwl)
			log(LOG_AUTHPRIV | LOG_NOTICE,
			    "ip6fw: Entry %d cleared.\n", frwl->fw_number);
		else
			log(LOG_AUTHPRIV | LOG_NOTICE,
			    "ip6fw: Accounting cleared.\n");
	}

	return(0);
}