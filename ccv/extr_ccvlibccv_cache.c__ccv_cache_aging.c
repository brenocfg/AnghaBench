#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int set; int bitmap; int age; } ;
struct TYPE_5__ {int off; int /*<<< orphan*/  type; } ;
struct TYPE_7__ {TYPE_2__ branch; TYPE_1__ terminal; } ;
typedef  TYPE_3__ ccv_cache_index_t ;

/* Variables and functions */
 int CCV_GET_TERMINAL_AGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bits_in_16bits_init ; 
 int compute_bits (int) ; 
 int /*<<< orphan*/  precomputed_16bits () ; 

__attribute__((used)) static void _ccv_cache_aging(ccv_cache_index_t* branch, uint64_t sign)
{
	if (!bits_in_16bits_init)
		precomputed_16bits();
	int i;
	uint64_t j = 63;
	ccv_cache_index_t* breadcrumb[10];
	for (i = 0; i < 10; i++)
	{
		breadcrumb[i] = branch;
		int leaf = branch->terminal.off & 0x1;
		int full = branch->terminal.off & 0x2;
		if (leaf)
		{
			break;
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
					break;
				}
			}
			j <<= 6;
		}
	}
	assert(i < 10);
	for (; i >= 0; i--)
	{
		branch = breadcrumb[i];
		int leaf = branch->terminal.off & 0x1;
		if (!leaf)
		{
			ccv_cache_index_t* set = (ccv_cache_index_t*)(branch->branch.set - (branch->branch.set & 0x3));
			uint32_t total = compute_bits(branch->branch.bitmap);
			uint32_t min_age = (set[0].terminal.off & 0x1) ? CCV_GET_TERMINAL_AGE(set[0].terminal.type) : set[0].branch.age;
			for (j = 1; j < total; j++)
			{
				uint32_t age = (set[j].terminal.off & 0x1) ? CCV_GET_TERMINAL_AGE(set[j].terminal.type) : set[j].branch.age;
				if (age < min_age)
					min_age = age;
			}
			branch->branch.age = min_age;
		}
	}
}