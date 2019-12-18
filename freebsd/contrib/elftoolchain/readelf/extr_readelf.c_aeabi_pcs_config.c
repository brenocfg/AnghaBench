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
typedef  int /*<<< orphan*/  s_pcs ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_pcs_config(uint64_t pcs)
{
	static char s_pcs[32];

	switch (pcs) {
	case 0: return "None";
	case 1: return "Bare platform";
	case 2: return "Linux";
	case 3: return "Linux DSO";
	case 4: return "Palm OS 2004";
	case 5: return "Palm OS (future)";
	case 6: return "Symbian OS 2004";
	case 7: return "Symbian OS (future)";
	default:
		snprintf(s_pcs, sizeof(s_pcs), "Unknown (%ju)",
		    (uintmax_t) pcs);
		return (s_pcs);
	}
}