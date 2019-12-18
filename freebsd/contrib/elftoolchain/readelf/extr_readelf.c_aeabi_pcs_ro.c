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
typedef  int /*<<< orphan*/  s_ro ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_pcs_ro(uint64_t ro)
{
	static char s_ro[32];

	switch (ro) {
	case 0: return "Absolute";
	case 1: return "PC-relative";
	case 2: return "None";
	default:
		snprintf(s_ro, sizeof(s_ro), "Unknown (%ju)", (uintmax_t) ro);
		return (s_ro);
	}
}