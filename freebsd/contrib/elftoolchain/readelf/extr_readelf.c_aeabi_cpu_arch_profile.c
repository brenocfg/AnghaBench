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
typedef  int /*<<< orphan*/  s_arch_profile ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_cpu_arch_profile(uint64_t pf)
{
	static char s_arch_profile[32];

	switch (pf) {
	case 0:
		return "Not applicable";
	case 0x41:		/* 'A' */
		return "Application Profile";
	case 0x52:		/* 'R' */
		return "Real-Time Profile";
	case 0x4D:		/* 'M' */
		return "Microcontroller Profile";
	case 0x53:		/* 'S' */
		return "Application or Real-Time Profile";
	default:
		snprintf(s_arch_profile, sizeof(s_arch_profile),
		    "Unknown (%ju)\n", (uintmax_t) pf);
		return (s_arch_profile);
	}
}