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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  s_va ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_vfp_args(uint64_t va)
{
	static char s_va[32];

	switch (va) {
	case 0: return "AAPCS (base variant)";
	case 1: return "AAPCS (VFP variant)";
	case 2: return "toolchain-specific";
	default:
		snprintf(s_va, sizeof(s_va), "Unknown (%ju)", (uintmax_t) va);
		return (s_va);
	}
}