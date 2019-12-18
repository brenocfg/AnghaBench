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
typedef  int /*<<< orphan*/  s_cpu_arch ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_cpu_arch(uint64_t arch)
{
	static char s_cpu_arch[32];

	switch (arch) {
	case 0: return "Pre-V4";
	case 1: return "ARM v4";
	case 2: return "ARM v4T";
	case 3: return "ARM v5T";
	case 4: return "ARM v5TE";
	case 5: return "ARM v5TEJ";
	case 6: return "ARM v6";
	case 7: return "ARM v6KZ";
	case 8: return "ARM v6T2";
	case 9: return "ARM v6K";
	case 10: return "ARM v7";
	case 11: return "ARM v6-M";
	case 12: return "ARM v6S-M";
	case 13: return "ARM v7E-M";
	default:
		snprintf(s_cpu_arch, sizeof(s_cpu_arch),
		    "Unknown (%ju)", (uintmax_t) arch);
		return (s_cpu_arch);
	}
}