#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
struct TYPE_10__ {int bitmap; int set; } ;
struct TYPE_9__ {int off; int sign; int /*<<< orphan*/  type; } ;
struct TYPE_12__ {TYPE_2__ branch; TYPE_1__ terminal; } ;
struct TYPE_11__ {scalar_t__ rnum; int age; int /*<<< orphan*/  size; TYPE_4__ origin; } ;
typedef  TYPE_3__ ccv_cache_t ;
typedef  TYPE_4__ ccv_cache_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_GET_CACHE_TYPE (int /*<<< orphan*/ ) ; 
 int CCV_GET_TERMINAL_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_cache_aging (TYPE_4__*,int) ; 
 int /*<<< orphan*/  _ccv_cache_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bits_in_16bits_init ; 
 scalar_t__ ccrealloc (TYPE_4__*,int) ; 
 int compute_bits (int) ; 
 int /*<<< orphan*/  precomputed_16bits () ; 

void* ccv_cache_out(ccv_cache_t* cache, uint64_t sign, uint8_t* type)
{
	if (!bits_in_16bits_init)
		precomputed_16bits();
	if (cache->rnum == 0)
		return 0;
	int i, found = 0, depth = -1;
	ccv_cache_index_t* parent = 0;
	ccv_cache_index_t* uncle = &cache->origin;
	ccv_cache_index_t* branch = &cache->origin;
	uint64_t j = 63;
	for (i = 0; i < 10; i++)
	{
		int leaf = branch->terminal.off & 0x1;
		int full = branch->terminal.off & 0x2;
		if (leaf)
		{
			found = 1;
			break;
		}
		if (parent != 0 && compute_bits(parent->branch.bitmap) > 1)
			uncle = branch;
		parent = branch;
		depth = i;
		ccv_cache_index_t* set = (ccv_cache_index_t*)(branch->branch.set - (branch->branch.set & 0x3));
		int dice = (sign & j) >> (i * 6);
		if (full)
		{
			branch = set + dice;
		} else {
			uint64_t k = 1;
			k = k << dice;
			if (k & branch->branch.bitmap)
			{
				uint64_t m = (k - 1) & branch->branch.bitmap;
				branch = set + compute_bits(m);
			} else {
				return 0;
			}
		}
		j <<= 6;
	}
	if (!found)
		return 0;
	int leaf = branch->terminal.off & 0x1;
	if (!leaf)
		return 0;
	if (branch->terminal.sign != sign)
		return 0;
	void* result = (void*)(branch->terminal.off - (branch->terminal.off & 0x3));
	if (type)
		*type = CCV_GET_CACHE_TYPE(branch->terminal.type);
	uint32_t size = CCV_GET_TERMINAL_SIZE(branch->terminal.type);
	if (branch != &cache->origin)
	{
		uint64_t k = 1, j = 63;
		int dice = (sign & (j << (depth * 6))) >> (depth * 6);
		k = k << dice;
		uint64_t m = (k - 1) & parent->branch.bitmap;
		uint32_t start = compute_bits(m);
		uint32_t total = compute_bits(parent->branch.bitmap);
		assert(total > 1);
		ccv_cache_index_t* set = (ccv_cache_index_t*)(parent->branch.set - (parent->branch.set & 0x3));
		if (total > 2 || (total == 2 && !(set[1 - start].terminal.off & 0x1)))
		{
			parent->branch.bitmap &= ~k;
			for (i = start + 1; i < total; i++)
				set[i - 1] = set[i];
			set = (ccv_cache_index_t*)ccrealloc(set, sizeof(ccv_cache_index_t) * (total - 1));
			parent->branch.set = (uint64_t)set;
		} else {
			ccv_cache_index_t t = set[1 - start];
			_ccv_cache_cleanup(uncle);
			*uncle = t;
		}
		_ccv_cache_aging(&cache->origin, sign);
	} else {
		// if I only have one item, reset age to 1
		cache->age = 1;
	}
	cache->rnum--;
	cache->size -= size;
	return result;
}