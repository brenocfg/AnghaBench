#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {int ifbit; int const hash; int d; } ;
typedef  TYPE_1__ ccv_nnc_cse_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int _ccv_nnc_cse_hash_find(ccv_nnc_cse_hash_t* const hash_map, const uint64_t hash, const int map_size)
{
	assert(hash > 0);
	int i, j;
	i = (hash - 1) % map_size;
	for (j = 0; ; j++, i++)
	{
		if (i >= map_size)
			i = 0;
		if (j > hash_map[i].ifbit)
			return -1;
		if (hash_map[i].hash == hash)
			return hash_map[i].d;
	}
}