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
typedef  int /*<<< orphan*/  s_ti ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_thumb_isa(uint64_t ti)
{
	static char s_ti[32];

	switch (ti) {
	case 0: return "No";
	case 1: return "16-bit Thumb";
	case 2: return "32-bit Thumb";
	default:
		snprintf(s_ti, sizeof(s_ti), "Unknown (%ju)\n",
		    (uintmax_t) ti);
		return (s_ti);
	}
}