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
typedef  int /*<<< orphan*/  s_r9 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_pcs_r9(uint64_t r9)
{
	static char s_r9[32];

	switch (r9) {
	case 0: return "V6";
	case 1: return "SB";
	case 2: return "TLS pointer";
	case 3: return "Unused";
	default:
		snprintf(s_r9, sizeof(s_r9), "Unknown (%ju)", (uintmax_t) r9);
		return (s_r9);
	}
}