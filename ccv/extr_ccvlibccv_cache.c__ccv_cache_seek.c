#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_7__ {int set; int bitmap; } ;
struct TYPE_6__ {int off; } ;
struct TYPE_8__ {TYPE_2__ branch; TYPE_1__ terminal; } ;
typedef  TYPE_3__ ccv_cache_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  bits_in_16bits_init ; 
 int compute_bits (int) ; 
 int /*<<< orphan*/  precomputed_16bits () ; 

__attribute__((used)) static ccv_cache_index_t* _ccv_cache_seek(ccv_cache_index_t* branch, uint64_t sign, int* depth)
{
	if (!bits_in_16bits_init)
		precomputed_16bits();
	int i;
	uint64_t j = 63;
	for (i = 0; i < 10; i++)
	{
		int leaf = branch->terminal.off & 0x1;
		int full = branch->terminal.off & 0x2;
		if (leaf)
		{
			if (depth)
				*depth = i;
			return branch;
		} else {
			ccv_cache_index_t* set = (ccv_cache_index_t*)(branch->branch.set - (branch->branch.set & 0x3));
			int dice = (sign & j) >> (i * 6);
			if (full)
			{
				branch = set + dice;
			} else {
				uint64_t k = 1;
				k = k << dice;
				if (k & branch->branch.bitmap) {
					uint64_t m = (k - 1) & branch->branch.bitmap;
					branch = set + compute_bits(m);
				} else {
					if (depth)
						*depth = i;
					return branch;
				}
			}
			j <<= 6;
		}
	}
	return 0;
}