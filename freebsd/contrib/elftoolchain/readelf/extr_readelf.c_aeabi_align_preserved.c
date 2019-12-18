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
typedef  int /*<<< orphan*/  s_align_p ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_align_preserved(uint64_t ap)
{
	static char s_align_p[128];

	switch (ap) {
	case 0: return "No";
	case 1: return "8-byte align";
	case 2: return "8-byte align and SP % 8 == 0";
	case 3: return "Reserved";
	default:
		if (ap >= 4 && ap <= 12)
			snprintf(s_align_p, sizeof(s_align_p), "8-byte align"
			    " and SP %% 8 == 0 and up to 2^%ju-byte extended"
			    " align", (uintmax_t) ap);
		else
			snprintf(s_align_p, sizeof(s_align_p), "Unknown (%ju)",
			    (uintmax_t) ap);
		return (s_align_p);
	}
}