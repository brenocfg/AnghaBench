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
 int /*<<< orphan*/  memmove (int* const,int* const,int) ; 

__attribute__((used)) static inline int _ccv_nnc_try_mix(int* const md, const int ins, const int c)
{
	if (!c)
	{
		md[0] = ins;
		return 1;
	}
	int ll = 0, uu = c - 1;
	int mm;
	do {
		mm = ll + ((uu - ll) >> 1);
		if (ins == md[mm])
			return 0;
		else if (ins < md[mm])
			uu = mm - 1;
		else if (ins > md[mm])
			ll = mm + 1;
	} while (ll <= uu);
	if (ll < c)
		memmove(md + ll + 1, md + ll, sizeof(int) * (c - ll));
	md[ll] = ins;
	return 1;
}