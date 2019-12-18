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
typedef  int /*<<< orphan*/  s_got ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_pcs_got(uint64_t got)
{
	static char s_got[32];

	switch (got) {
	case 0: return "None";
	case 1: return "direct";
	case 2: return "indirect via GOT";
	default:
		snprintf(s_got, sizeof(s_got), "Unknown (%ju)",
		    (uintmax_t) got);
		return (s_got);
	}
}