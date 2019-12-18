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
typedef  int /*<<< orphan*/  s_wa ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_wmmx_args(uint64_t wa)
{
	static char s_wa[32];

	switch (wa) {
	case 0: return "AAPCS (base variant)";
	case 1: return "Intel WMMX";
	case 2: return "toolchain-specific";
	default:
		snprintf(s_wa, sizeof(s_wa), "Unknown(%ju)", (uintmax_t) wa);
		return (s_wa);
	}
}