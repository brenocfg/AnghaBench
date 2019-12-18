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
struct uwb_rsv_alloc_info {int max_interval; scalar_t__* bm; int /*<<< orphan*/  unsafe_allocated_mases; int /*<<< orphan*/  safe_allocated_mases; int /*<<< orphan*/  max_mas; int /*<<< orphan*/  min_mas; } ;
struct uwb_rsv {int max_interval; int /*<<< orphan*/  max_mas; int /*<<< orphan*/  min_mas; } ;
struct uwb_mas_bm {int /*<<< orphan*/  unsafe; int /*<<< orphan*/  safe; int /*<<< orphan*/  unsafe_bm; int /*<<< orphan*/  bm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int UWB_NUM_MAS ; 
 scalar_t__ UWB_RSV_ALLOC_FOUND ; 
 int UWB_RSV_ALLOC_NOT_FOUND ; 
 scalar_t__ UWB_RSV_MAS_NOT_AVAIL ; 
 scalar_t__ UWB_RSV_MAS_SAFE ; 
 scalar_t__ UWB_RSV_MAS_UNSAFE ; 
 int /*<<< orphan*/  bitmap_or (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  get_column_descriptors (struct uwb_rsv_alloc_info*) ; 
 int /*<<< orphan*/  get_row_descriptors (struct uwb_rsv_alloc_info*) ; 
 int /*<<< orphan*/  kfree (struct uwb_rsv_alloc_info*) ; 
 struct uwb_rsv_alloc_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 
 scalar_t__ uwb_rsv_find_best_col_alloc (struct uwb_rsv_alloc_info*,int) ; 
 scalar_t__ uwb_rsv_find_best_row_alloc (struct uwb_rsv_alloc_info*) ; 

int uwb_rsv_find_best_allocation(struct uwb_rsv *rsv, struct uwb_mas_bm *available, 
				 struct uwb_mas_bm *result)
{
	struct uwb_rsv_alloc_info *ai;
	int interval;
	int bit_index;

	ai = kzalloc(sizeof(struct uwb_rsv_alloc_info), GFP_KERNEL);
	
	ai->min_mas = rsv->min_mas;
	ai->max_mas = rsv->max_mas;
	ai->max_interval = rsv->max_interval;


	/* fill the not available vector from the available bm */
	for (bit_index = 0; bit_index < UWB_NUM_MAS; bit_index++) {
		if (!test_bit(bit_index, available->bm))
			ai->bm[bit_index] = UWB_RSV_MAS_NOT_AVAIL;
	}

	if (ai->max_interval == 1) {
		get_row_descriptors(ai);
		if (uwb_rsv_find_best_row_alloc(ai) == UWB_RSV_ALLOC_FOUND)
			goto alloc_found;
		else
			goto alloc_not_found;
	}

	get_column_descriptors(ai);
        
	for (interval = 16; interval >= 2; interval>>=1) {
		if (interval > ai->max_interval)
			continue;
		if (uwb_rsv_find_best_col_alloc(ai, interval) == UWB_RSV_ALLOC_FOUND)
			goto alloc_found;
	}

	/* try row reservation if no column is found */
	get_row_descriptors(ai);
	if (uwb_rsv_find_best_row_alloc(ai) == UWB_RSV_ALLOC_FOUND)
		goto alloc_found;
	else
		goto alloc_not_found;

  alloc_found:
	bitmap_zero(result->bm, UWB_NUM_MAS);
	bitmap_zero(result->unsafe_bm, UWB_NUM_MAS);
	/* fill the safe and unsafe bitmaps */
	for (bit_index = 0; bit_index < UWB_NUM_MAS; bit_index++) {
		if (ai->bm[bit_index] == UWB_RSV_MAS_SAFE)
			set_bit(bit_index, result->bm);
		else if (ai->bm[bit_index] == UWB_RSV_MAS_UNSAFE)
			set_bit(bit_index, result->unsafe_bm);
	}
	bitmap_or(result->bm, result->bm, result->unsafe_bm, UWB_NUM_MAS);

	result->safe   = ai->safe_allocated_mases;
	result->unsafe = ai->unsafe_allocated_mases;
	
	kfree(ai);		
	return UWB_RSV_ALLOC_FOUND;
  
  alloc_not_found:
	kfree(ai);
	return UWB_RSV_ALLOC_NOT_FOUND;
}