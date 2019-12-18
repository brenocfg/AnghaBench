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
typedef  int /*<<< orphan*/  s_wmmx ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_wmmx_arch(uint64_t wmmx)
{
	static char s_wmmx[32];

	switch (wmmx) {
	case 0: return "No";
	case 1: return "WMMXv1";
	case 2: return "WMMXv2";
	default:
		snprintf(s_wmmx, sizeof(s_wmmx), "Unknown (%ju)",
		    (uintmax_t) wmmx);
		return (s_wmmx);
	}
}