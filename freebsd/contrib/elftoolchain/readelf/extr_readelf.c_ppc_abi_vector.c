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
typedef  int /*<<< orphan*/  s_vec ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
ppc_abi_vector(uint64_t vec)
{
	static char s_vec[64];

	switch (vec) {
	case 0: return "N/A";
	case 1: return "Generic purpose registers";
	case 2: return "AltiVec registers";
	case 3: return "SPE registers";
	default:
		snprintf(s_vec, sizeof(s_vec), "Unknown(%ju)", (uintmax_t) vec);
		return (s_vec);
	}
}