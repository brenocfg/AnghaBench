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
struct TYPE_6__ {int off; } ;
struct TYPE_7__ {int set; int /*<<< orphan*/  bitmap; } ;
struct TYPE_8__ {TYPE_1__ terminal; TYPE_2__ branch; } ;
typedef  TYPE_3__ ccv_cache_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_3__*) ; 
 int compute_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_cache_cleanup(ccv_cache_index_t* branch)
{
	int leaf = branch->terminal.off & 0x1;
	if (!leaf)
	{
		int i;
		uint64_t total = compute_bits(branch->branch.bitmap);
		ccv_cache_index_t* set = (ccv_cache_index_t*)(branch->branch.set - (branch->branch.set & 0x3));
		for (i = 0; i < total; i++)
		{
			if (!(set[i].terminal.off & 0x1))
				_ccv_cache_cleanup(set + i);
		}
		ccfree(set);
	}
}