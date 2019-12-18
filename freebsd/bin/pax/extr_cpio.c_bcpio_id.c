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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  HD_BCPIO ;

/* Variables and functions */
 scalar_t__ MAGIC ; 
 scalar_t__ RSHRT_EXT (char*) ; 
 scalar_t__ SHRT_EXT (char*) ; 
 int /*<<< orphan*/  swp_head ; 

int
bcpio_id(char *blk, int size)
{
	if (size < (int)sizeof(HD_BCPIO))
		return(-1);

	/*
	 * check both normal and byte swapped magic cookies
	 */
	if (((u_short)SHRT_EXT(blk)) == MAGIC)
		return(0);
	if (((u_short)RSHRT_EXT(blk)) == MAGIC) {
		if (!swp_head)
			++swp_head;
		return(0);
	}
	return(-1);
}