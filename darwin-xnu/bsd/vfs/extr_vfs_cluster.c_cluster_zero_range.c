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
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  upl_page_info_t ;
typedef  int off_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int IO_NOZERODIRTY ; 
 int IO_NOZEROVALID ; 
 int PAGE_MASK_64 ; 
 scalar_t__ PAGE_SIZE ; 
 int PAGE_SIZE_64 ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  cluster_zero (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int min (int,scalar_t__) ; 
 scalar_t__ upl_valid_page (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
cluster_zero_range(upl_t upl, upl_page_info_t *pl, int flags, int io_offset, off_t zero_off, off_t upl_f_offset, int bytes_to_zero)
{
	int zero_pg_index;
	boolean_t need_cluster_zero = TRUE;

        if ((flags & (IO_NOZEROVALID | IO_NOZERODIRTY))) {

	        bytes_to_zero = min(bytes_to_zero, PAGE_SIZE - (int)(zero_off & PAGE_MASK_64));
		zero_pg_index = (int)((zero_off - upl_f_offset) / PAGE_SIZE_64);

		if (upl_valid_page(pl, zero_pg_index)) {
			/*
			 * never force zero valid pages - dirty or clean
			 * we'll leave these in the UPL for cluster_write_copy to deal with
			 */
			need_cluster_zero = FALSE;
		} 
	}
	if (need_cluster_zero == TRUE)
		cluster_zero(upl, io_offset, bytes_to_zero, NULL);

	return (bytes_to_zero);
}