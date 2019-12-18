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

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_1T_SEGMENT ; 
 scalar_t__ GET_ESID (unsigned long) ; 
 scalar_t__ GET_ESID_1T (unsigned long) ; 
 unsigned long SID_SHIFT_1T ; 
 int /*<<< orphan*/  cpu_has_feature (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int esids_match(unsigned long addr1, unsigned long addr2)
{
	int esid_1t_count;

	/* System is not 1T segment size capable. */
	if (!cpu_has_feature(CPU_FTR_1T_SEGMENT))
		return (GET_ESID(addr1) == GET_ESID(addr2));

	esid_1t_count = (((addr1 >> SID_SHIFT_1T) != 0) +
				((addr2 >> SID_SHIFT_1T) != 0));

	/* both addresses are < 1T */
	if (esid_1t_count == 0)
		return (GET_ESID(addr1) == GET_ESID(addr2));

	/* One address < 1T, the other > 1T.  Not a match */
	if (esid_1t_count == 1)
		return 0;

	/* Both addresses are > 1T. */
	return (GET_ESID_1T(addr1) == GET_ESID_1T(addr2));
}