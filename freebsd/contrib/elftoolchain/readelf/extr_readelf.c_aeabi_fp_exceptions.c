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
typedef  int /*<<< orphan*/  s_fp_e ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_fp_exceptions(uint64_t fe)
{
	static char s_fp_e[32];

	switch (fe) {
	case 0: return "Unused";
	case 1: return "Needed";
	default:
		snprintf(s_fp_e, sizeof(s_fp_e), "Unknown (%ju)",
		    (uintmax_t) fe);
		return (s_fp_e);
	}
}