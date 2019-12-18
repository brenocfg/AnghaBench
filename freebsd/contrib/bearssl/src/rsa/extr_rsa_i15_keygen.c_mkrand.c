#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* generate ) (TYPE_1__ const**,int*,size_t) ;} ;
typedef  TYPE_1__ br_prng_class ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__ const**,int*,size_t) ; 

__attribute__((used)) static void
mkrand(const br_prng_class **rng, uint16_t *x, uint32_t esize)
{
	size_t u, len;
	unsigned m;

	len = (esize + 15) >> 4;
	(*rng)->generate(rng, x + 1, len * sizeof(uint16_t));
	for (u = 1; u < len; u ++) {
		x[u] &= 0x7FFF;
	}
	m = esize & 15;
	if (m == 0) {
		x[len] &= 0x7FFF;
	} else {
		x[len] &= 0x7FFF >> (15 - m);
	}
}