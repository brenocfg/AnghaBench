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
typedef  int /*<<< orphan*/  s_fp_16 ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_fp_16bit_format(uint64_t fp16)
{
	static char s_fp_16[64];

	switch (fp16) {
	case 0: return "None";
	case 1: return "IEEE 754";
	case 2: return "VFPv3/Advanced SIMD (alternative format)";
	default:
		snprintf(s_fp_16, sizeof(s_fp_16), "Unknown (%ju)",
		    (uintmax_t) fp16);
		return (s_fp_16);
	}
}