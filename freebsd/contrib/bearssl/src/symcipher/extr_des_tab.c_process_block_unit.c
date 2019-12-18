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
typedef  int uint32_t ;

/* Variables and functions */
 int Fconf (int,int const,int const) ; 

__attribute__((used)) static void
process_block_unit(uint32_t *pl, uint32_t *pr, const uint32_t *skey)
{
	int i;
	uint32_t l, r;

	l = *pl;
	r = *pr;
	for (i = 0; i < 16; i ++) {
		uint32_t t;

		t = l ^ Fconf(r, skey[(i << 1) + 0], skey[(i << 1) + 1]);
		l = r;
		r = t;
	}
	*pl = r;
	*pr = l;
}