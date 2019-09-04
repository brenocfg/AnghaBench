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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u_int16_t ;

/* Variables and functions */
 scalar_t__ get_combining_class (scalar_t__) ; 

__attribute__((used)) static void
prioritysort(u_int16_t* characters, int count)
{
	u_int32_t p1, p2;
	u_int16_t *ch1, *ch2;
	u_int16_t *end;
	int changes = 0;

	end = characters + count;
	do {
		changes = 0;
		ch1 = characters;
		ch2 = characters + 1;
		p2 = get_combining_class(*ch1);
		while (ch2 < end) {
			p1 = p2;
			p2 = get_combining_class(*ch2);
			if (p1 > p2 && p2 != 0) {
				u_int32_t tmp;

				tmp = *ch1;
				*ch1 = *ch2;
				*ch2 = tmp;
				changes = 1;
				
				/*
				 * Make sure that p2 contains the combining class for the
				 * character now stored at *ch2.  This isn't required for
				 * correctness, but it will be more efficient if a character
				 * with a large combining class has to "bubble past" several
				 * characters with lower combining classes.
				 */
				p2 = p1;
			}
			++ch1;
			++ch2;
		}
	} while (changes);
}