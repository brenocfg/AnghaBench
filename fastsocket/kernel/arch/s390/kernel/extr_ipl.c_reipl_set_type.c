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
typedef  enum ipl_type { ____Placeholder_ipl_type } ipl_type ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  IPL_TYPE_CCW 132 
#define  IPL_TYPE_FCP 131 
#define  IPL_TYPE_FCP_DUMP 130 
#define  IPL_TYPE_NSS 129 
#define  IPL_TYPE_UNKNOWN 128 
 int /*<<< orphan*/  MACHINE_IS_VM ; 
 int /*<<< orphan*/  REIPL_METHOD_CCW_CIO ; 
 int /*<<< orphan*/  REIPL_METHOD_CCW_DIAG ; 
 int /*<<< orphan*/  REIPL_METHOD_CCW_VM ; 
 int /*<<< orphan*/  REIPL_METHOD_DEFAULT ; 
 int /*<<< orphan*/  REIPL_METHOD_FCP_DUMP ; 
 int /*<<< orphan*/  REIPL_METHOD_FCP_RO_DIAG ; 
 int /*<<< orphan*/  REIPL_METHOD_FCP_RO_VM ; 
 int /*<<< orphan*/  REIPL_METHOD_FCP_RW_DIAG ; 
 int /*<<< orphan*/  REIPL_METHOD_NSS ; 
 int /*<<< orphan*/  REIPL_METHOD_NSS_DIAG ; 
 int /*<<< orphan*/  diag308_set_works ; 
 int /*<<< orphan*/  reipl_block_actual ; 
 int /*<<< orphan*/  reipl_block_ccw ; 
 int /*<<< orphan*/  reipl_block_fcp ; 
 int /*<<< orphan*/  reipl_block_nss ; 
 int reipl_capabilities ; 
 int /*<<< orphan*/  reipl_method ; 
 int reipl_type ; 

__attribute__((used)) static int reipl_set_type(enum ipl_type type)
{
	if (!(reipl_capabilities & type))
		return -EINVAL;

	switch(type) {
	case IPL_TYPE_CCW:
		if (diag308_set_works)
			reipl_method = REIPL_METHOD_CCW_DIAG;
		else if (MACHINE_IS_VM)
			reipl_method = REIPL_METHOD_CCW_VM;
		else
			reipl_method = REIPL_METHOD_CCW_CIO;
		reipl_block_actual = reipl_block_ccw;
		break;
	case IPL_TYPE_FCP:
		if (diag308_set_works)
			reipl_method = REIPL_METHOD_FCP_RW_DIAG;
		else if (MACHINE_IS_VM)
			reipl_method = REIPL_METHOD_FCP_RO_VM;
		else
			reipl_method = REIPL_METHOD_FCP_RO_DIAG;
		reipl_block_actual = reipl_block_fcp;
		break;
	case IPL_TYPE_FCP_DUMP:
		reipl_method = REIPL_METHOD_FCP_DUMP;
		break;
	case IPL_TYPE_NSS:
		if (diag308_set_works)
			reipl_method = REIPL_METHOD_NSS_DIAG;
		else
			reipl_method = REIPL_METHOD_NSS;
		reipl_block_actual = reipl_block_nss;
		break;
	case IPL_TYPE_UNKNOWN:
		reipl_method = REIPL_METHOD_DEFAULT;
		break;
	default:
		BUG();
	}
	reipl_type = type;
	return 0;
}