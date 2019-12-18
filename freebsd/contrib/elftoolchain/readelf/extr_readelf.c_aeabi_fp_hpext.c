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
typedef  int /*<<< orphan*/  s_fh ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_fp_hpext(uint64_t fh)
{
	static char s_fh[32];

	switch (fh) {
	case 0: return "Not allowed";
	case 1: return "Allowed";
	default:
		snprintf(s_fh, sizeof(s_fh), "Unknown(%ju)", (uintmax_t) fh);
		return (s_fh);
	}
}