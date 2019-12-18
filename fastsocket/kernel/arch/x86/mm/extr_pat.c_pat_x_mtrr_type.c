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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 scalar_t__ MTRR_TYPE_WRBACK ; 
 unsigned long _PAGE_CACHE_UC_MINUS ; 
 unsigned long _PAGE_CACHE_WB ; 
 scalar_t__ mtrr_type_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long pat_x_mtrr_type(u64 start, u64 end, unsigned long req_type)
{
	/*
	 * Look for MTRR hint to get the effective type in case where PAT
	 * request is for WB.
	 */
	if (req_type == _PAGE_CACHE_WB) {
		u8 mtrr_type;

		mtrr_type = mtrr_type_lookup(start, end);
		if (mtrr_type != MTRR_TYPE_WRBACK)
			return _PAGE_CACHE_UC_MINUS;

		return _PAGE_CACHE_WB;
	}

	return req_type;
}