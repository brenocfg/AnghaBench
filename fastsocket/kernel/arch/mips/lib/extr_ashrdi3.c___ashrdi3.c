#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int word_type ;
struct TYPE_3__ {int high; int low; } ;
struct TYPE_4__ {long long ll; TYPE_1__ s; } ;
typedef  TYPE_2__ DWunion ;

/* Variables and functions */

long long __ashrdi3(long long u, word_type b)
{
	DWunion uu, w;
	word_type bm;

	if (b == 0)
		return u;

	uu.ll = u;
	bm = 32 - b;

	if (bm <= 0) {
		/* w.s.high = 1..1 or 0..0 */
		w.s.high =
		    uu.s.high >> 31;
		w.s.low = uu.s.high >> -bm;
	} else {
		const unsigned int carries = (unsigned int) uu.s.high << bm;

		w.s.high = uu.s.high >> b;
		w.s.low = ((unsigned int) uu.s.low >> b) | carries;
	}

	return w.ll;
}