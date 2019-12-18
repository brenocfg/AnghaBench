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
typedef  scalar_t__ u16 ;

/* Variables and functions */
 scalar_t__ AMD_VSA_SIG ; 
 scalar_t__ GSW_VSA_SIG ; 
 int /*<<< orphan*/  VSA_VRC_DATA ; 
 int /*<<< orphan*/  VSA_VRC_INDEX ; 
 int /*<<< orphan*/  VSA_VR_SIGNATURE ; 
 int /*<<< orphan*/  VSA_VR_UNLOCK ; 
 scalar_t__ inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int geode_has_vsa2(void)
{
	static int has_vsa2 = -1;

	if (has_vsa2 == -1) {
		u16 val;

		/*
		 * The VSA has virtual registers that we can query for a
		 * signature.
		 */
		outw(VSA_VR_UNLOCK, VSA_VRC_INDEX);
		outw(VSA_VR_SIGNATURE, VSA_VRC_INDEX);

		val = inw(VSA_VRC_DATA);
		has_vsa2 = (val == AMD_VSA_SIG || val == GSW_VSA_SIG);
	}

	return has_vsa2;
}