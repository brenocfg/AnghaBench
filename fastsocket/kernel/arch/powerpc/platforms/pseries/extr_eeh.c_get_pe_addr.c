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
struct eeh_early_enable_info {int /*<<< orphan*/  buid_lo; int /*<<< orphan*/  buid_hi; } ;

/* Variables and functions */
 scalar_t__ RTAS_UNKNOWN_SERVICE ; 
 scalar_t__ ibm_get_config_addr_info ; 
 scalar_t__ ibm_get_config_addr_info2 ; 
 int rtas_call (scalar_t__,int,int,unsigned int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int get_pe_addr (int config_addr,
                        struct eeh_early_enable_info *info)
{
	unsigned int rets[3];
	int ret;

	/* Use latest config-addr token on power6 */
	if (ibm_get_config_addr_info2 != RTAS_UNKNOWN_SERVICE) {
		/* Make sure we have a PE in hand */
		ret = rtas_call (ibm_get_config_addr_info2, 4, 2, rets,
			config_addr, info->buid_hi, info->buid_lo, 1);
		if (ret || (rets[0]==0))
			return 0;

		ret = rtas_call (ibm_get_config_addr_info2, 4, 2, rets,
			config_addr, info->buid_hi, info->buid_lo, 0);
		if (ret)
			return 0;
		return rets[0];
	}

	/* Use older config-addr token on power5 */
	if (ibm_get_config_addr_info != RTAS_UNKNOWN_SERVICE) {
		ret = rtas_call (ibm_get_config_addr_info, 4, 2, rets,
			config_addr, info->buid_hi, info->buid_lo, 0);
		if (ret)
			return 0;
		return rets[0];
	}
	return 0;
}