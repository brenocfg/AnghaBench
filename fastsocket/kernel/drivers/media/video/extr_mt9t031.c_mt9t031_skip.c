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
typedef  int u16 ;
typedef  int s32 ;

/* Variables and functions */
 int min (int,int) ; 

__attribute__((used)) static u16 mt9t031_skip(s32 *source, s32 target, s32 max)
{
	unsigned int skip;

	if (*source < target + target / 2) {
		*source = target;
		return 1;
	}

	skip = min(max, *source + target / 2) / target;
	if (skip > 8)
		skip = 8;
	*source = target * skip;

	return skip;
}