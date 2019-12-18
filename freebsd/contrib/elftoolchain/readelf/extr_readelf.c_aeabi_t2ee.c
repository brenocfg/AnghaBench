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
typedef  int /*<<< orphan*/  s_t2ee ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *
aeabi_t2ee(uint64_t t2ee)
{
	static char s_t2ee[32];

	switch (t2ee) {
	case 0: return "Not allowed";
	case 1: return "Allowed";
	default:
		snprintf(s_t2ee, sizeof(s_t2ee), "Unknown(%ju)",
		    (uintmax_t) t2ee);
		return (s_t2ee);
	}

}