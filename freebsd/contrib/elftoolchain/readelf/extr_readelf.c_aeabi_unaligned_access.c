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
typedef  int /*<<< orphan*/  s_ua ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_unaligned_access(uint64_t ua)
{
	static char s_ua[32];

	switch (ua) {
	case 0: return "Not allowed";
	case 1: return "Allowed";
	default:
		snprintf(s_ua, sizeof(s_ua), "Unknown(%ju)", (uintmax_t) ua);
		return (s_ua);
	}
}