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
typedef  scalar_t__ ppnum_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ atop (scalar_t__) ; 
 scalar_t__ avail_end ; 
 scalar_t__ first_avail ; 

boolean_t
pmap_next_page(
	ppnum_t *pnum)
{
	if (first_avail != avail_end) {
		*pnum = (ppnum_t)atop(first_avail);
		first_avail += PAGE_SIZE;
		return TRUE;
	}
	return FALSE;
}