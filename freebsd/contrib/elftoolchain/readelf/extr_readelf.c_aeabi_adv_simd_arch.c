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
typedef  int /*<<< orphan*/  s_simd ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_adv_simd_arch(uint64_t simd)
{
	static char s_simd[32];

	switch (simd) {
	case 0: return "No";
	case 1: return "NEONv1";
	case 2: return "NEONv2";
	default:
		snprintf(s_simd, sizeof(s_simd), "Unknown (%ju)",
		    (uintmax_t) simd);
		return (s_simd);
	}
}