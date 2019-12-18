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
struct fddi_mib {int /*<<< orphan*/  fddiSMTConnectionPolicy; } ;
struct s_smc {struct fddi_mib mib; } ;

/* Variables and functions */
 char OEMID (struct s_smc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POLICY_MM ; 

__attribute__((used)) static void set_oem_spec_val(struct s_smc *smc)
{
	struct fddi_mib *mib ;

	mib = &smc->mib ;

	/*
	 * set IBM specific values
	 */
	if (OEMID(smc,0) == 'I') {
		mib->fddiSMTConnectionPolicy = POLICY_MM ;
	}
}