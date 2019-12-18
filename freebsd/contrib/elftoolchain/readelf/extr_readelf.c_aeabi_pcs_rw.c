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
typedef  int /*<<< orphan*/  s_rw ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_pcs_rw(uint64_t rw)
{
	static char s_rw[32];

	switch (rw) {
	case 0: return "Absolute";
	case 1: return "PC-relative";
	case 2: return "SB-relative";
	case 3: return "None";
	default:
		snprintf(s_rw, sizeof(s_rw), "Unknown (%ju)", (uintmax_t) rw);
		return (s_rw);
	}
}