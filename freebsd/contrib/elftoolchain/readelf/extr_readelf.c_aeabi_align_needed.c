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
typedef  int /*<<< orphan*/  s_align_n ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_align_needed(uint64_t an)
{
	static char s_align_n[64];

	switch (an) {
	case 0: return "No";
	case 1: return "8-byte align";
	case 2: return "4-byte align";
	case 3: return "Reserved";
	default:
		if (an >= 4 && an <= 12)
			snprintf(s_align_n, sizeof(s_align_n), "8-byte align"
			    " and up to 2^%ju-byte extended align",
			    (uintmax_t) an);
		else
			snprintf(s_align_n, sizeof(s_align_n), "Unknown (%ju)",
			    (uintmax_t) an);
		return (s_align_n);
	}
}