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
typedef  int /*<<< orphan*/  s_virtual ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_virtual(uint64_t vt)
{
	static char s_virtual[64];

	switch (vt) {
	case 0: return "No";
	case 1: return "TrustZone";
	case 2: return "Virtualization extension";
	case 3: return "TrustZone and virtualization extension";
	default:
		snprintf(s_virtual, sizeof(s_virtual), "Unknown(%ju)",
		    (uintmax_t) vt);
		return (s_virtual);
	}
}